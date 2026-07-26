//! @file IO/HierarchySerialization.cpp
//! @brief The definition of an object which manages a deserialized hierarchy
//! of objects.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////

#include "Ag/IO/BufferedInputStream.hpp"
#include "Ag/IO/Exceptions.hpp"
#include "Ag/IO/HierarchySerialization.hpp"
#include "BinaryReaderWriters.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// ObjectReader Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty object reader.
ObjectReader::ObjectReader() :
    _reader(nullptr)
{
}

//! @brief Creates an object ready to read a serialized object.
//! @param[in] reader The implementation of the object reader.
ObjectReader::ObjectReader(IObjectReader *reader) :
    _reader(reader)
{
}

//! @brief Acquires an object reader from another wrapper.
//! @param[in] rhs The object to acquire the reader implementation from.
ObjectReader::ObjectReader(ObjectReader &&rhs) noexcept :
    _reader(std::exchange(rhs._reader, nullptr))
{
}

//! @brief Ensures any wrapped reader is properly disposed of.
ObjectReader::~ObjectReader()
{
    safeDelete(_reader);
}

//! @brief Determines if the object is bound to an underlying reader implementation.
//! @retval true The object has a reader and will return values.
//! @retval false The object is unbound and will not return any useful values.
bool ObjectReader::isBound() const
{
    return (_reader != nullptr);
}

//! @brief Determines if the object contains a named property.
//! @param[in] tag The property identifier.
//! @retval true The object contains a serialized value for the property
//! identified by @p tag.
//! @retval false The object contains no properties matching @p tag.
bool ObjectReader::hasProperty(string_cref_t tag) const
{
    return (_reader != nullptr) && _reader->hasProperty(tag);
}

//! @brief Gets the storage size of a named property.
//! @param[in] tag The property identifier.
//! @return The count of bytes used to store the specified property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException Thrown if the @p tag doesn't match
//! any property in the object.
StreamLength ObjectReader::getPropertySize(string_cref_t tag) const
{
    StreamLength propSize;

    if (verifyAccess("get property size")->tryGetPropertySize(tag, propSize))
        return propSize;

    throw PropertyNotFoundException(tag);
}

//! @brief Attempts to get the storage size of a named property.
//! @param[in] tag The property identifier.
//! @param[out] propSize Receives the count of bytes used to store the
//! specified property value.
//! @retval true The property existed and @p propSize was updated with
//! its size.
//! @retval false The property could not be found.
bool ObjectReader::tryGetPropertySize(string_cref_t tag,
                                       StreamLength &propSize) const
{
    propSize = -1;

    return (_reader != nullptr) && _reader->tryGetPropertySize(tag, propSize);
}

//! @brief Replaces the currently wrapped reader implementation with another.
//! @param[in] rhs The wrapper to acquire the reader implementation from.
//! @return A reference to the current object.
ObjectReader &ObjectReader::operator=(ObjectReader &&rhs) noexcept
{
    if (_reader != rhs._reader)
    {
        safeDelete(_reader);

        _reader = std::exchange(rhs._reader, nullptr);
    }

    return *this;
}

//! @brief Attempts to read a serialized boolean property from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a bool.
bool ObjectReader::tryRead(string_cref_t tag, bool &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized signed 8-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, int8_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized unsigned 8-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, uint8_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized signed 16-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, int16_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized unsigned 16-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, uint16_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized signed 32-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, int32_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized unsigned 32-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, uint32_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized signed 64-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, int64_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized unsigned 64-bit integer property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an integer of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, uint64_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized Unicode character property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a character.
bool ObjectReader::tryRead(string_cref_t tag, char32_t &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized 32-bit floating point property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a real scalar of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, float &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized 64-bit floating point property
//! from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a bool.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a real scalar of appropriate size.
bool ObjectReader::tryRead(string_cref_t tag, double &value) const
{
    value = false;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized string property from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the value of the property on success.
//! @retval true The property was found and could be interpreted as a string.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a string.
bool ObjectReader::tryRead(string_cref_t tag, Ag::String &value) const
{
    value = String::Empty;

    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a byte block property from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the block of bytes the property contains
//! on success.
//! @retval true The property was found and could be interpreted as a block
//! of bytes.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a block of bytes.
bool ObjectReader::tryRead(string_cref_t tag, ByteBlock &value) const
{
    return (_reader != nullptr) &&
           _reader->tryRead(tag, value);
}

//! @brief Attempts to read a stream block property from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives a stream to access the field bytes on success.
//! @retval true The property was found and could be interpreted as a block
//! of bytes.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as a block of bytes.
bool ObjectReader::tryRead(string_cref_t tag, ISeekableStreamUPtr &value) const
{
    value.reset();

    return (_reader != nullptr) &&
        _reader->tryRead(tag, value);
}

//! @brief Attempts to read a serialized object property from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the reader of the nested object on success.
//! @retval true The property was found and could be interpreted as an object.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an object.
bool ObjectReader::tryRead(string_cref_t tag, ObjectReader &value) const
{
    IObjectReader *reader = nullptr;

    if ((_reader == nullptr) ||
        (_reader->tryRead(tag, reader) == false))
    {
        value = { };

        return false;
    }

    value = { reader };
    return true;
}

//! @brief Attempts to read a serialized array property from the object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives the reader of the nested array on success.
//! @retval true The property was found and could be interpreted as an array.
//! @retval false No property matching @p tag could be found, or it could, but
//! it could not be interpreted as an array.
bool ObjectReader::tryRead(string_cref_t tag, ArrayReader &value) const
{
    IArrayReader *reader = nullptr;

    if ((_reader == nullptr) ||
        (_reader->tryRead(tag, reader) == false))
    {
        value = { };

        return false;
    }

    value = { reader };
    return true;
}

//! @brief Reads a serialized boolean property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! a bool.
bool ObjectReader::readBool(string_cref_t tag) const
{
    return read<bool>(tag, "boolean");
}

//! @brief Reads a serialized signed 8-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
int8_t ObjectReader::readInt8(string_cref_t tag) const
{
    return read<int8_t>(tag, "signed 8-bit integer");
}

//! @brief Reads a serialized signed 8-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
uint8_t ObjectReader::readUint8(string_cref_t tag) const
{
    return read<uint8_t>(tag, "unsigned 8-bit integer");
}

//! @brief Reads a serialized signed 16-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
int16_t ObjectReader::readInt16(string_cref_t tag) const
{
    return read<int16_t>(tag, "signed 16-bit integer");
}

//! @brief Reads a serialized signed 16-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
uint16_t ObjectReader::readUint16(string_cref_t tag) const
{
    return read<uint16_t>(tag, "unsigned 16-bit integer");
}

//! @brief Reads a serialized signed 32-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
int32_t ObjectReader::readInt32(string_cref_t tag) const
{
    return read<int32_t>(tag, "signed 32-bit integer");
}

//! @brief Reads a serialized signed 32-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
uint32_t ObjectReader::readUint32(string_cref_t tag) const
{
    return read<uint32_t>(tag, "unsigned 32-bit integer");
}

//! @brief Reads a serialized signed 64-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
int64_t ObjectReader::readInt64(string_cref_t tag) const
{
    return read<int64_t>(tag, "signed 64-bit integer");
}

//! @brief Reads a serialized signed 64-bit integer property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! an integer of appropriate size.
uint64_t ObjectReader::readUint64(string_cref_t tag) const
{
    return read<uint64_t>(tag, "unsigned 64-bit integer");
}

//! @brief Reads a serialized Unicode character property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! character.
char32_t ObjectReader::readChar(string_cref_t tag) const
{
    return read<char32_t>(tag, "character");
}

//! @brief Reads a serialized single-precision floating point property from
//! the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! a scalar.
float ObjectReader::readFloat(string_cref_t tag) const
{
    return read<float>(tag, "float");
}

//! @brief Reads a serialized single-precision floating point property from
//! the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! a scalar.
double ObjectReader::readDouble(string_cref_t tag) const
{
    return read<double>(tag, "double");
}

//! @brief Reads a serialized string property from the object.
//! @param[in] tag The identifier of the property to read.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! a string.
String ObjectReader::readString(string_cref_t tag) const
{
    return read<String>(tag, "string");
}

//! @brief Reads a property encoded with a block of bytes.
//! @return The property value.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! a block of bytes.
ByteBlock ObjectReader::readBytes(string_cref_t tag) const
{
    return read<ByteBlock>(tag, "bytes");
}

//! @brief Reads a property encoded with a stream of bytes.
//! @return A stream used to access the bytes of the field.
//! @throws ObjectNotBoundException If the object is in an unbound state.
//! @throws PropertyNotFoundException If the property does not exist.
//! @throws PropertyTypeException If the property cannot be interpreted as
//! a block of bytes.
ISeekableStreamUPtr ObjectReader::readBytesStream(string_cref_t tag) const
{
    return read<ISeekableStreamUPtr>(tag, "bytes");
}

//! @brief Reads a property as a nested object.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives a new reader object on success, which the
//! caller is responsible for disposing of.
//! @retval true There was an element left to read and it could be
//! interpreted as an object. A new reader for the object was created,
//! a pointer to which was written to @p value.
//! @retval false Either there were no more values in the array to read,
//! or the next value could not be interpreted as an object.
ObjectReader ObjectReader::readObject(string_cref_t tag) const
{
    IObjectReader *nestedReader = read<IObjectReader *>(tag, "nested object");

    return ObjectReader(nestedReader);
}

//! @brief Reads a property as a nested array.
//! @param[in] tag The identifier of the property to read.
//! @param[out] value Receives a new reader object on success, which the
//! caller is responsible for disposing of.
//! @retval true There was an element left to read and it could be
//! interpreted as an array. A new reader for the array was created,
//! a pointer to which was written to @p value.
//! @retval false Either there were no more values in the array to read,
//! or the next value could not be interpreted as an array.
ArrayReader ObjectReader::readArray(string_cref_t tag) const
{
    IArrayReader *nestedReader = read<IArrayReader *>(tag, "nested object");

    return ArrayReader(nestedReader);
}

//! @brief Ensures the object is in a bound state before returning the
//! underlying implementation.
//! @param[in] op A description of the operation requesting the implementation.
//! @return A pointer to the object reader implementation.
//! @throws ObjectNotBoundException Thrown if the object is not in a bound state.
IObjectReader *ObjectReader::verifyAccess(utf8_cptr_t op) const
{
    if (_reader == nullptr)
        throw ObjectNotBoundException("ObjectReader", op);

    return _reader;
}

////////////////////////////////////////////////////////////////////////////////
// ObjectWriter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty writer.
ObjectWriter::ObjectWriter() :
    _writer(nullptr)
{
}

//! @brief Creates an object wrapping an object writer implementation.
//! @param[in] writer The writer implementation to take ownership of.
ObjectWriter::ObjectWriter(IObjectWriter *writer) :
    _writer(writer)
{
}

//! @brief Creates an object which acquires a writer implementation from
//! another instance.
//! @param[in] rhs The instance to acquire the writer from.
ObjectWriter::ObjectWriter(ObjectWriter &&rhs) noexcept :
    _writer(std::exchange(rhs._writer, nullptr))
{
}

//! @brief Ensures the wrapped writer is properly disposed of.
ObjectWriter::~ObjectWriter()
{
    safeDelete(_writer);
}

//! @brief Determines if the object is bound to an underlying writer.
//! @retval true The object is bound to a writer and all operations will
//! work correctly.
//! @retval false The object us unbound and all operations will raise an
//! ObjectNotBoundException.
bool ObjectWriter::isBound() const
{
    return (_writer != nullptr);
}

//! @brief Acquires a writer implementation from another wrapper.
//! @param[in] rhs The wrapper to acquire the writer from.
//! @return A reference to the current object.
ObjectWriter &ObjectWriter::operator=(ObjectWriter &&rhs) noexcept
{
    if (_writer != rhs._writer)
    {
        safeDelete(_writer);

        _writer = std::exchange(rhs._writer, nullptr);
    }

    return *this;
}

//! @brief Writes a boolean property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, bool value)
{
    verifyAccess("write bool")->write(tag, value);
}

//! @brief Writes a signed 8-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, int8_t value)
{
    verifyAccess("write signed 8-bit integer")->write(tag, value);
}

//! @brief Writes an unsigned 8-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, uint8_t value)
{
    verifyAccess("write unsigned 8-bit integer")->write(tag, value);
}

//! @brief Writes a signed 16-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, int16_t value)
{
    verifyAccess("write signed 16-bit integer")->write(tag, value);
}

//! @brief Writes an unsigned 16-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, uint16_t value)
{
    verifyAccess("write unsigned 16-bit integer")->write(tag, value);
}

//! @brief Writes a signed 32-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, int32_t value)
{
    verifyAccess("write signed 32-bit integer")->write(tag, value);
}

//! @brief Writes an unsigned 32-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, uint32_t value)
{
    verifyAccess("write unsigned 32-bit integer")->write(tag, value);
}

//! @brief Writes a signed 64-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, int64_t value)
{
    verifyAccess("write signed 64-bit integer")->write(tag, value);
}

//! @brief Writes an unsigned 64-bit integer property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, uint64_t value)
{
    verifyAccess("write unsigned 64-bit integer")->write(tag, value);
}

//! @brief Writes a Unicode character property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, char32_t value)
{
    verifyAccess("write character")->write(tag, value);
}

//! @brief Writes a 32-bit floating point property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, float value)
{
    verifyAccess("write float")->write(tag, value);
}

//! @brief Writes a 64-bit floating point property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, double value)
{
    verifyAccess("write double")->write(tag, value);
}

//! @brief Writes a string property to the serialized object.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value The value of the property to write.
void ObjectWriter::write(string_cref_t tag, string_cref_t value)
{
    verifyAccess("write string")->write(tag, value);
}

//! @brief Writes a property containing a block of bytes.
//! @param[in] tag The tag identifying the property being written.
//! @param[in] value A pointer to the first byte to be written.
//! @param[in] byteCount The count of bytes pointed to by @p value.
void ObjectWriter::write(string_cref_t tag, const void *value, size_t byteCount)
{
    verifyAccess("write bytes")->write(tag, value, byteCount);
}

//! @brief Begins writing a stream of bytes.
//! @param[in] tag The identifier used to retrieve the object during
//! deserialization.
//! @return An stream used to write bytes to which the caller is responsible
//! for disposing of, and must be disposed of before any more properties are
//! written to the current object.
IStreamUPtr ObjectWriter::beginWriteBytes(string_cref_t tag)
{
    return verifyAccess("write byte stream")->beginWriteBytes(tag);
}

//! @brief Begins writing a nested object.
//! @param[in] tag The identifier used to retrieve the object during
//! deserialization.
//! @return An object used to write the nested object which
//! the caller is responsible for disposing of, and must be disposed of
//! before any more properties are written to the current object.
ObjectWriter ObjectWriter::beginWriteObject(string_cref_t tag)
{
    return { verifyAccess("write nested object")->beginWriteObject(tag) };
}

//! @brief Begins writing a nested array.
//! @param[in] tag The identifier used to retrieve the array during
//! deserialization.
//! @return A pointer to an object used to write the nested array which
//! the caller is responsible for disposing of, and must be disposed of
//! before any more properties are written to the current object.
ArrayWriter ObjectWriter::beginWriteArray(string_cref_t tag)
{
    return { verifyAccess("write nested array")->beginWriteArray(tag) };
}

//! @brief Verifies that the object is still bound to an underlying writer
//! before a write operation.
//! @param[in] op Details of the operation being performed.
//! @return A valid object writer.
//! @throws ObjectNotBoundException Thrown if the object is not currently
//! bound to an underlying writer.
IObjectWriter *ObjectWriter::verifyAccess(utf8_cptr_t op)
{
    if (_writer == nullptr)
        throw ObjectNotBoundException("ArrayWriter", op);

    return _writer;
}

////////////////////////////////////////////////////////////////////////////////
// ArrayReader Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty array reader.
ArrayReader::ArrayReader() :
    _reader(nullptr)
{
}

//! @brief Creates an object ready to read a serialized array.
//! @param[in] reader The implementation of the array reader.
ArrayReader::ArrayReader(IArrayReader *reader) :
    _reader(reader)
{
}

//! @brief Acquires an array reader from another wrapper.
//! @param[in] rhs The object to acquire the reader implementation from.
ArrayReader::ArrayReader(ArrayReader &&rhs) noexcept :
    _reader(std::exchange(rhs._reader, nullptr))
{
}

//! @brief Ensures any wrapped reader is properly disposed of.
ArrayReader::~ArrayReader()
{
    safeDelete(_reader);
}

//! @brief Determines if the object is bound to an underlying reader implementation.
//! @retval true The object has a reader and will return values.
//! @retval false The object is unbound and will not return any useful values.
bool ArrayReader::isBound() const noexcept
{
    return (_reader != nullptr);
}

//! @brief Determines if the reader is currently positioned on a value.
//! @retval true The object points to a collection element.
//! @retval false The object points to the end of the collection.
bool ArrayReader::hasMore() const
{
    return (_reader != nullptr) && _reader->hasMore();
}

//! @brief Obtain the storage size of the next element to be read.
//! @throw ObjectNotBoundException Thrown if the reader is in an unbound state.
//! @throws DataFormatException Thrown if there are no more elements in
//! the collection.
StreamLength ArrayReader::getNextElementSize() const
{
    StreamLength elementSize;

    if (verifyElementAccess("get element size")->tryGetNextElementSize(elementSize))
        return elementSize;

    throw DataFormatException("No next property.");
}

//! @brief Attempts to obtain the size of the next element to be read.
//! @param[out] elementSize Receives the count of bytes used to store the
//! next array element value on success.
//! @retval true The object points to a collection element and its size was
//! copied to @p elementSize.
//! @retval false There were no more collection elements.
bool ArrayReader::tryGetNextElementSize(StreamLength &elementSize) const
{
    elementSize = -1;

    return (_reader != nullptr) &&
           _reader->tryGetNextElementSize(elementSize);
}

//! @brief Gets the count of elements in the collection.
StreamLength ArrayReader::getElementCount() const
{
    return (_reader == nullptr) ? 0 : _reader->getElementCount();
}

//! @brief Gets the 0-based index of the item the array is poised
//! to read next.
StreamPosition ArrayReader::getCurrentElementIndex() const
{
    return (_reader == nullptr) ? 0 : _reader->getCurrentElementIndex();
}

// Resets the array so that the next value read will be the first.
void ArrayReader::reset()
{
    verifyAccess("reset position")->reset();
}

//! @brief Skips a number of subsequent elements.
//! @param[in] count The non-negative count of elements to skip.
void ArrayReader::skip(StreamLength count)
{
    verifyAccess("skip elements")->skip(count);
}

//! @brief Replaces the currently wrapped reader implementation with another.
//! @param[in] rhs The wrapper to acquire the reader implementation from.
//! @return A reference to the current object.
ArrayReader &ArrayReader::operator=(ArrayReader &&rhs) noexcept
{
    if (_reader != rhs._reader)
    {
        safeDelete(_reader);

        _reader = std::exchange(rhs._reader, nullptr);
    }

    return *this;
}

//! @brief Attempts to read the next element of the array as a boolean value.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a bool. The value was written to @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as a bool.
bool ArrayReader::tryReadNext(bool &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a
//! signed 8-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(int8_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as an
//! unsigned 8-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(uint8_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a
//! signed 16-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(int16_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as an
//! unsigned 16-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(uint16_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a
//! signed 32-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(int32_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as an
//! unsigned 32-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(uint32_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a
//! signed 64-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(int64_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as an
//! unsigned 64-bit integer.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an integer of appropriate size. The value was written to
//! @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as an integer of appropriate size.
bool ArrayReader::tryReadNext(uint64_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a Unicode character.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a character. The value was written to @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as a character.
bool ArrayReader::tryReadNext(char32_t &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a 32-bit
//! floating point scalar.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a scalar of appropriate size. The value was written to @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as a scalar of appropriate size.
bool ArrayReader::tryReadNext(float &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a 64-bit
//! floating point scalar.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a scalar of appropriate size. The value was written to @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as a scalar of appropriate size.
bool ArrayReader::tryReadNext(double &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a string.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a string. The value was written to @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as a string.
bool ArrayReader::tryReadNext(String &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element of the array as a block of bytes.
//! @param[out] value The value of the element on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a block of bytes. The value was written to @p value.
//! @retval false Either there were no move values in the array to read,
//! or the next value could not be interpreted as a block of bytes.
bool ArrayReader::tryReadNext(ByteBlock &value)
{
    return (_reader != nullptr) && _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element as a stream of bytes.
//! @param[out] value Receives a new stream on success.
//! @retval true There was an element left to read and it could be
//! interpreted as a stream of bytes. A new stream for the block was created,
//! and used to overwrite @p value.
//! @retval false Either there were no more values in the array to read,
//! or the next value could not be interpreted as a block of bytes.
bool ArrayReader::tryReadNext(ISeekableStreamUPtr &value)
{
    value.reset();

    return (_reader != nullptr) &&
           _reader->tryReadNext(value);
}

//! @brief Attempts to read the next element as a nested object.
//! @param[out] value Receives a new reader object on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an object. A new reader for the object was created,
//! and used to overwrite @p value.
//! @retval false Either there were no more values in the array to read,
//! or the next value could not be interpreted as an object.
bool ArrayReader::tryReadNext(ObjectReader &value)
{
    IObjectReader *nestedReader = nullptr;

    if ((_reader != nullptr) && _reader->tryReadNext(nestedReader))
    {
        value = { nestedReader };

        return true;
    }

    return false;
}

//! @brief Attempts to read the next element as a nested array.
//! @param[out] value Receives a new reader object on success.
//! @retval true There was an element left to read and it could be
//! interpreted as an array. A new reader for the array was created,
//! and used to overwrite @p value.
//! @retval false Either there were no more values in the array to read,
//! or the next value could not be interpreted as an array.
bool ArrayReader::tryReadNext(ArrayReader &value)
{
    IArrayReader *nestedReader = nullptr;

    if ((_reader != nullptr) && _reader->tryReadNext(nestedReader))
    {
        value = { nestedReader };

        return true;
    }

    return false;
}

//! @brief Reads the next element of the array as a boolean value.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as a bool.
bool ArrayReader::readNextBool()
{
    return readNext<bool>("bool");
}

//! @brief Reads the next element of the array as a signed 8-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
int8_t ArrayReader::readNextInt8()
{
    return readNext<int8_t>("signed 8-bit integer");
}

//! @brief Reads the next element of the array as an unsigned 8-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
uint8_t ArrayReader::readNextUint8()
{
    return readNext<uint8_t>("unsigned 8-bit integer");
}

//! @brief Reads the next element of the array as a signed 16-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
int16_t ArrayReader::readNextInt16()
{
    return readNext<int16_t>("signed 16-bit integer");
}

//! @brief Reads the next element of the array as an unsigned 16-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
uint16_t ArrayReader::readNextUint16()
{
    return readNext<uint16_t>("unsigned 16-bit integer");
}

//! @brief Reads the next element of the array as a signed 32-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
int32_t ArrayReader::readNextInt32()
{
    return readNext<int32_t>("signed 32-bit integer");
}

//! @brief Reads the next element of the array as an unsigned 32-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
uint32_t ArrayReader::readNextUint32()
{
    return readNext<uint32_t>("unsigned 32-bit integer");
}

//! @brief Reads the next element of the array as a signed 64-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
int64_t ArrayReader::readNextInt64()
{
    return readNext<int64_t>("signed 64-bit integer");
}

//! @brief Reads the next element of the array as an unsigned 64-bit integer.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as an integer of appropriate size.
uint64_t ArrayReader::readNextUint64()
{
    return readNext<uint64_t>("unsigned 64-bit integer");
}

//! @brief Reads the next element of the array as a Unicode character.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as a character.
char32_t ArrayReader::readNextChar()
{
    return readNext<char32_t>("character");
}

//! @brief Reads the next element of the array as a 32-bit floating point scalar.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as a scalar.
float ArrayReader::readNextFloat()
{
    return readNext<float>("float");
}

//! @brief Reads the next element of the array as a 64-bit floating point scalar.
//! @return The value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as a scalar.
double ArrayReader::readNextDouble()
{
    return readNext<double>("double");
}

//! @brief Reads the next element of the array as a string.
//! @return The string value of the next element.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as a string.
String ArrayReader::readNextString()
{
    return readNext<String>("string");
}

//! @brief Reads the next element of the array as a block of bytes.
//! @return The next element as a block of bytes.
//! @throws DataFormatException If there are no more elements available or
//! the next element cannot be interpreted as a block of bytes.
ByteBlock ArrayReader::readNextBytes()
{
    return readNext<ByteBlock>("bytes");
}

//! @brief Reads the next element as a stream of bytes.
//! @return A stream used to read the bytes of the element.
ISeekableStreamUPtr ArrayReader::readNextByteStream()
{
    return readNext<ISeekableStreamUPtr>("byte stream");
}

//! @brief Reads the next element as a nested object.
//! @return A reader for the nested object.
ObjectReader ArrayReader::readNextObject()
{
    IObjectReader *nestedReader = readNext<IObjectReader *>("nested object");

    return { nestedReader };
}

//! @brief Reads the next element as a nested array.
//! @return A reader for the nested array.
ArrayReader ArrayReader::readNextArray()
{
    IArrayReader *nestedReader = readNext<IArrayReader *>("nested array");

    return { nestedReader };
}

//! @brief Verifies that the object is in a bound state.
//! @param[in] op A description of the operation attempting to access the 
//! underlying reader.
//! @return A pointer to the reader.
//! @throws ObjectNotBoundException Thrown if the object is not bound to an
//! underlying reader.
IArrayReader *ArrayReader::verifyAccess(utf8_cptr_t op) const
{
    if (_reader == nullptr)
        throw ObjectNotBoundException("ArrayReader", op);

    return _reader;
}

//! @brief Verifies that the object is in a bound state and positioned on
//! a valid field.
//! @param[in] op A description of the operation attempting to access the 
//! underlying reader.
//! @return A pointer to the reader.
//! @throws ObjectNotBoundException Thrown if the object is not bound to an
//! underlying reader.
//! @throws DataFromatException Thrown if there are no more elements available.
IArrayReader *ArrayReader::verifyElementAccess(utf8_cptr_t op) const
{
    IArrayReader *reader = verifyAccess(op);

    if (reader->hasMore() == false)
        throw DataFormatException("No more elements were available in the array.");

    return reader;
}

////////////////////////////////////////////////////////////////////////////////
// ArrayWriter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty writer.
ArrayWriter::ArrayWriter() :
    _writer(nullptr)
{
}

//! @brief Creates an object wrapping an array writer implementation.
//! @param[in] writer The writer implementation to take ownership of.
ArrayWriter::ArrayWriter(IArrayWriter *writer) :
    _writer(writer)
{
}

//! @brief Creates an object which acquires a writer implementation from
//! another instance.
//! @param[in] rhs The instance to acquire the writer from.
ArrayWriter::ArrayWriter(ArrayWriter &&rhs) noexcept :
    _writer(std::exchange(rhs._writer, nullptr))
{
}

//! @brief Ensures the wrapped writer is properly disposed of.
ArrayWriter::~ArrayWriter()
{
    safeDelete(_writer);
}

//! @brief Determines if the object is bound to an underlying writer.
//! @retval true The object is bound to a writer and all operations will
//! work correctly.
//! @retval false The object us unbound and all operations will raise an
//! ObjectNotBoundException.
bool ArrayWriter::isBound() const
{
    return (_writer != nullptr);
}

//! @brief Acquires a writer implementation from another wrapper.
//! @param[in] rhs The wrapper to acquire the writer from.
//! @return A reference to the current object.
ArrayWriter &ArrayWriter::operator=(ArrayWriter &&rhs) noexcept
{
    if (_writer != rhs._writer)
    {
        safeDelete(_writer);

        _writer = std::exchange(rhs._writer, nullptr);
    }

    return *this;
}

//! @brief Writes a boolean value as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(bool value)
{
    verifyAccess("write bool")->write(value);
}

//! @brief Writes a signed 8-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(int8_t value)
{
    verifyAccess("write signed 8-bit integer")->write(value);
}

//! @brief Writes an unsigned 8-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(uint8_t value)
{
    verifyAccess("write unsigned 8-bit integer")->write(value);
}

//! @brief Writes a signed 16-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(int16_t value)
{
    verifyAccess("write signed 16-bit integer")->write(value);
}

//! @brief Writes an unsigned 16-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(uint16_t value)
{
    verifyAccess("write unsigned 16-bit integer")->write(value);
}

//! @brief Writes a signed 32-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(int32_t value)
{
    verifyAccess("write signed 32-bit integer")->write(value);
}

//! @brief Writes an unsigned 32-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(uint32_t value)
{
    verifyAccess("write unsigned 32-bit integer")->write(value);
}

//! @brief Writes a signed 64-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(int64_t value)
{
    verifyAccess("write signed 64-bit integer")->write(value);
}

//! @brief Writes an unsigned 64-bit integer as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(uint64_t value)
{
    verifyAccess("write unsigned 64-bit integer")->write(value);
}

//! @brief Writes a Unicode character as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(char32_t value)
{
    verifyAccess("write character")->write(value);
}

//! @brief Writes a 32-bit floating point value as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(float value)
{
    verifyAccess("write float")->write(value);
}

//! @brief Writes a 64-bit floating point value as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(double value)
{
    verifyAccess("write double")->write(value);
}

//! @brief Writes a string value as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(string_cref_t value)
{
    verifyAccess("write string")->write(value);
}

//! @brief Writes a block of bytes as the next element in the collection.
//! @param[in] value The value to write.
void ArrayWriter::write(const void *value, size_t byteCount)
{
    verifyAccess("write bytes")->write(value, byteCount);
}

//! @brief Begins writing a stream of bytes as the next element in the collection.
//! @return An object used to write the field bytes, which must be disposed
//! of before any more elements are written to the current array.
IStreamUPtr ArrayWriter::beginWriteBytes()
{
    return verifyAccess("write bytes")->beginWriteBytes();
}

//! @brief Begins writing a object as the next element in the collection.
//! @return An object used to write the nested object which must be disposed
//! of before any more elements are written to the current array.
ObjectWriter ArrayWriter::beginWriteObject()
{
    return { verifyAccess("write nested object")->beginWriteObject() };
}

//! @brief Begins writing a nested array as the next element in the collection.
//! @return An object used to write the nested array which
//! must be disposed of before any more elements are written to the
//! current array.
ArrayWriter ArrayWriter::beginWriteArray()
{
    return { verifyAccess("write nested object")->beginWriteArray() };
}

//! @brief Verifies that the object is still bound to an underlying writer
//! before a write operation.
//! @param[in] op Details of the operation being performed.
//! @return A valid object writer.
//! @throws ObjectNotBoundException Thrown if the object is not currently
//! bound to an underlying writer.
IArrayWriter *ArrayWriter::verifyAccess(utf8_cptr_t op)
{
    if (_writer == nullptr)
        throw ObjectNotBoundException("ArrayWriter", op);

    return _writer;
}

////////////////////////////////////////////////////////////////////////////////
// HierarchyRoot Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Reads an object hierarchy from an input stream.
//! @param[in] input The input stream to read the serialized data from.
HierarchyRoot::HierarchyRoot(IStream *input)
{
    // Buffer the input, both to batch reading, but also so that we can
    // analyse the first few bytes to see what format of stream we have.
    BufferedInputStream reader(input);

    // TODO: Analyse header bytes to determine the format.

    // For the moment, assume the stream is in the binary format.
    BinaryStreamHeader header;

    if (header.tryRead(&reader) == false)
        throw IOException("Failed to read binary hierarchy stream header.");

    header.validate();

    auto binaryRoot = std::make_shared<BinaryHierarchyRoot>(header, &reader);

    _root = binaryRoot;
}

//! @brief Ensures all resident deserialized data is disposed of.
HierarchyRoot::~HierarchyRoot()
{
}

//! @brief Determines if the root of the serialized hierarchy is an object.
//! @retval true The root of the serialized data is an object.
//! @retval false The root of the serialized data is not an object.
bool HierarchyRoot::hasRootObject() const
{
    if (auto hierRoot = std::dynamic_pointer_cast<HierarchyRootPrivate>(_root))
    {
        return hierRoot->hasRootObject();
    }

    return false;
}

//! @brief Determines if the root of the serialized hierarchy is an array.
//! @retval true The root of the serialized data is an array.
//! @retval false The root of the serialized data is not an array.
bool HierarchyRoot::hasRootArray() const
{
    if (auto hierRoot = std::dynamic_pointer_cast<HierarchyRootPrivate>(_root))
    {
        return hierRoot->hasRootArray();
    }

    return false;
}

//! @brief Gets an object representing the object at the root of the serialized data.
//! @remarks
//! The lifetime of the returned object and any further ObjectReader or ArrayReader
//! objects is produces is tied to the lifetime of this HierarchyRoot instance.
ObjectReader HierarchyRoot::getRootObject()
{
    if (auto hierRoot = std::dynamic_pointer_cast<HierarchyRootPrivate>(_root))
    {
        return ObjectReader(hierRoot->getRootObject());
    }

    return { };
}

//! @brief Gets an object representing the array at the root of the serialized data.
//! @remarks
//! The lifetime of the returned object and any further ObjectReader or ArrayReader
//! objects is produces is tied to the lifetime of this HierarchyRoot instance.
ArrayReader HierarchyRoot::getRootArray()
{
    if (auto hierRoot = std::dynamic_pointer_cast<HierarchyRootPrivate>(_root))
    {
        return ArrayReader(hierRoot->getRootArray());
    }

    return { };
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to write an array of elements to an output stream.
//! @param[in] output The output stream to write the elements to.
//! @param[in] compress True to compress the data before writing to output, false
//! to write it uncompressed.
//! @return An object used to write the array elements, the binary encoding of
//! which will be written to @p output when the object is destroyed.
ArrayWriter beginSerializeArray(ISeekableStream *output, bool compress)
{
    return ArrayWriter(new BinaryArrayWriter(output, compress));
}

//! @brief Constructs an object to write an set of named properties output stream.
//! @param[in] output The output stream to write the elements to.
//! @param[in] compress True to compress the data before writing to output, false
//! to write it uncompressed.
//! @return An object used to write the property set, the binary encoding of
//! which will be written to @p output when the object is destroyed.
ObjectWriter beginSerializeObject(ISeekableStream *output, bool compress)
{
    return ObjectWriter(new BinaryObjectWriter(output, compress));
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

