//! @file IO/HierarchyInterfaces.hpp
//! @brief The declaration of private interfaces necessary for hierarchy
//! serialization.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_HIERARCHY_INTERFACES_HPP_
#define HEADER_IO_HIERARCHY_INTERFACES_HPP_

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Memory.hpp"

#include "Ag/IO/ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class IArrayReader;
class IArrayWriter;

//! @brief An interface to an object which can access the properties of a
//! serialised object.
class IObjectReader
{
protected:
    // Construction/Destruction
    IObjectReader() = default;
public:
    virtual ~IObjectReader() = default;

    // Accessors

    //! @brief Determines if the object contains a named property.
    //! @param[in] tag The property identifier.
    //! @retval true The object contains a serialized value for the property
    //! identified by @p tag.
    //! @retval false The object contains no properties matching @p tag.
    virtual bool hasProperty(string_cref_t tag) const = 0;

    //! @brief Attempts to read the storage size of a named property.
    //! @param[in] tag The property identifier.
    //! @param[out] propSize Receives the count of bytes used to store the
    //! specified property value.
    //! @retval true The property existed and @p propSize was updated with
    //! its size.
    //! @retval false The property could not be found.
    virtual bool tryGetPropertySize(string_cref_t tag,
                                    StreamLength &propSize) const = 0;

    // Operations

    //! @brief Attempts to read the boolean value of a property.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as a bool.
    //! @retval true The property existed and could be interpreted as a bool.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a bool.
    virtual bool tryRead(string_cref_t tag, bool &value) const = 0;

    //! @brief Attempts to read the value of a property as a signed 8-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, int8_t &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! an unsigned 8-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, uint8_t &value) const = 0;

    //! @brief Attempts to read the value of a property as a signed 16-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, int16_t &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! an unsigned 16-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, uint16_t &value) const = 0;

    //! @brief Attempts to read the value of a property as a signed 32-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, int32_t &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! an unsigned 32-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, uint32_t &value) const = 0;

    //! @brief Attempts to read the value of a property as a signed 64-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, int64_t &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! an unsigned 64-bit integer.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as an integer of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as an integer of appropriate size.
    virtual bool tryRead(string_cref_t tag, uint64_t &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! a Unicode character.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as a character.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a character.
    virtual bool tryRead(string_cref_t tag, char32_t &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! a 32-bit floating point value.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as a scalar of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a scalar of appropriate size.
    virtual bool tryRead(string_cref_t tag, float &value) const = 0;

    //! @brief Attempts to read the value of a property as
    //! a 64-bit floating point value.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as a scalar of appropriate size.
    //! @retval true The property existed and could be interpreted as
    //! the appropriate type.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a scalar of appropriate size.
    virtual bool tryRead(string_cref_t tag, double &value) const = 0;

    //! @brief Attempts to read the string value of a property.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as a string.
    //! @retval true The property existed and could be interpreted as a string.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a string.
    virtual bool tryRead(string_cref_t tag, String &value) const =0;

    //! @brief Attempts to read a property value which is a block of bytes.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives the value if the property existed and could
    //! be interpreted as a block of bytes.
    //! @retval true The property existed and could be interpreted as a block
    //! of bytes.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a block of bytes.
    virtual bool tryRead(string_cref_t tag, ByteBlock &value) const =0;

    //! @brief Attempts to read a property value which is a block of bytes.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives a bytes stream if the property existed and
    //! could be interpreted as a block of bytes.
    //! @retval true The property existed and could be interpreted as a block
    //! of bytes.
    //! @retval false The property either didn't exist, or the value could not
    //! be interpreted as a block of bytes.
    virtual bool tryRead(string_cref_t tag, ISeekableStreamUPtr &value) const =0;

    //! @brief Attempts to read a property as a nested object.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives a new reader object on success, which the
    //! caller is responsible for disposing of.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an object. A new reader for the object was created,
    //! a pointer to which was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an object.
    virtual bool tryRead(string_cref_t tag, IObjectReader *&value) const = 0;

    //! @brief Attempts to read a property as a nested array.
    //! @param[in] tag The identifier of the property to read.
    //! @param[out] value Receives a new reader object on success, which the
    //! caller is responsible for disposing of.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an array. A new reader for the array was created,
    //! a pointer to which was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an array.
    virtual bool tryRead(string_cref_t tag, IArrayReader *&value) const = 0;
};

//! @brief An interface to an object which can be used to serialize the
//! properties of a serialised object.
class IObjectWriter
{
protected:
    // Construction/Destruction
    IObjectWriter() = default;
public:
    virtual ~IObjectWriter() = default;

    // Accessors

    // Operations

    //! @brief Writes a boolean value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value of the bool to write.
    virtual void write(string_cref_t tag, bool value) = 0;

    //! @brief Writes a signed 8-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, int8_t value) = 0;

    //! @brief Writes an unsigned 8-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, uint8_t value) = 0;

    //! @brief Writes a signed 16-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, int16_t value) = 0;

    //! @brief Writes an unsigned 16-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, uint16_t value) = 0;

    //! @brief Writes a signed 32-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, int32_t value) = 0;

    //! @brief Writes an unsigned 32-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, uint32_t value) = 0;

    //! @brief Writes a signed 64-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, int64_t value) = 0;

    //! @brief Writes an unsigned 64-bit integer value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, uint64_t value) = 0;

    //! @brief Writes a Unicode character value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, char32_t value) = 0;

    //! @brief Writes a 32-bit floating point value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, float value) = 0;

    //! @brief Writes a 64-bit floating point value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value to write.
    virtual void write(string_cref_t tag, double value) = 0;

    //! @brief Writes a string value as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value The value of the string to write.
    virtual void write(string_cref_t tag, string_cref_t value) = 0;

    //! @brief Writes a block of bytes as a named property.
    //! @param[in] tag The identifier of the property to write.
    //! @param[in] value A pointer to the first byte to write.
    //! @param[in] byteCount The count of bytes pointed to by @p value.
    virtual void write(string_cref_t tag, const void *value, size_t byteCount) =0;

    //! @brief Begins writing a block of bytes as a named property.
    //! @param[in] tag The identifier used to retrieve the block during
    //! deserialization.
    //! @return A pointer to an IStream implementation used to write the bytes
    //! which the caller is responsible for disposing of, and must be disposed
    //! of before any more properties are written to the current object.
    virtual IStreamUPtr beginWriteBytes(string_cref_t tag) =0;

    //! @brief Begins writing a nested object as a named property.
    //! @param[in] tag The identifier used to retrieve the object during
    //! deserialization.
    //! @return A pointer to an object used to write the nested object which
    //! the caller is responsible for disposing of, and must be disposed of
    //! before any more properties are written to the current object.
    virtual IObjectWriter *beginWriteObject(string_cref_t tag) = 0;

    //! @brief Begins writing a nested array as a named property.
    //! @param[in] tag The identifier used to retrieve the array during
    //! deserialization.
    //! @return A pointer to an object used to write the nested array which
    //! the caller is responsible for disposing of, and must be disposed of
    //! before any more properties are written to the current object.
    virtual IArrayWriter *beginWriteArray(string_cref_t tag) = 0;
};

//! @brief An interface to an object which can access the elements of a
//! serialised array.
class IArrayReader
{
protected:
    // Construction/Destruction
    IArrayReader() = default;
public:
    virtual ~IArrayReader() = default;

    // Accessors

    //! @brief Determines if the reader is currently positioned on a value.
    //! @retval true The object points to a collection element.
    //! @retval false The object points to the end of the collection.
    virtual bool hasMore() const = 0;

    //! @brief Attempts to obtain the size of the next element to be read.
    //! @param[out] elementSize Receives the count of bytes used to store the
    //! next array element value on success.
    //! @retval true The object points to a collection element and its size was
    //! copied to @p elementSize.
    //! @retval false There were no more collection elements.
    virtual bool tryGetNextElementSize(StreamLength &elementSize) const = 0;

    //! @brief Gets the count of elements in the collection.
    virtual StreamLength getElementCount() const = 0;

    //! @brief Gets the 0-based index of the item the array is poised
    //! to read next.
    virtual StreamPosition getCurrentElementIndex() const = 0;

    // Operations
    // Resets the array so that the next value read will be the first.
    virtual void reset() = 0;

    //! @brief Skips a number of subsequent elements.
    //! @param[in] count The non-negative count of elements to skip.
    virtual void skip(StreamLength count) = 0;

    //! @brief Attempts to read the next element of the array as a boolean value.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a bool. The value was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a bool.
    virtual bool tryReadNext(bool &value) = 0;

    //! @brief Attempts to read the next element of the array as a signed
    //! 8-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(int8_t &value) = 0;

    //! @brief Attempts to read the next element of the array as an unsigned
    //! 8-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(uint8_t &value) = 0;

    //! @brief Attempts to read the next element of the array as a signed
    //! 16-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(int16_t &value) = 0;

    //! @brief Attempts to read the next element of the array as an unsigned
    //! 16-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(uint16_t &value) = 0;

    //! @brief Attempts to read the next element of the array as a signed
    //! 32-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(int32_t &value) = 0;

    //! @brief Attempts to read the next element of the array as an unsigned
    //! 32-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(uint32_t &value) = 0;

    //! @brief Attempts to read the next element of the array as a signed
    //! 64-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(int64_t &value) = 0;

    //! @brief Attempts to read the next element of the array as an unsigned
    //! 64-bit integer.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an integer of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an integer of
    //! appropriate size.
    virtual bool tryReadNext(uint64_t &value) = 0;

    //! @brief Attempts to read the next element of the array as a
    //! Unicode character.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a character. The value was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a character.
    virtual bool tryReadNext(char32_t &value) = 0;

    //! @brief Attempts to read the next element of the array as a
    //! 32-bit floating point scalar.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a scalar of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a scalar of
    //! appropriate size.
    virtual bool tryReadNext(float &value) = 0;

    //! @brief Attempts to read the next element of the array as a
    //! 32-bit floating point scalar.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a scalar of appropriate size. The value was written
    //! to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a scalar of
    //! appropriate size.
    virtual bool tryReadNext(double &value) = 0;

    //! @brief Attempts to read the next element of the array as a string.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a string. The value was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a string.
    virtual bool tryReadNext(String &value) =0;

    //! @brief Attempts to read the next element of the array as a
    //! block of bytes.
    //! @param[out] value Receives the value of the element on success.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a block of bytes. The value was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a block of bytes.
    virtual bool tryReadNext(ByteBlock &value) =0;

    //! @brief Attempts to read the next element of the array as a
    //! block of bytes accessed via an IStream implementation.
    //! @param[out] value Receives the value of the element on success, which
    //! the caller is responsible for disposing of.
    //! @retval true There was an element left to read and it could be
    //! interpreted as a block of bytes. The stream was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as a block of bytes.
    virtual bool tryReadNext(ISeekableStreamUPtr &value) =0;

    //! @brief Attempts to read the next element as a nested object.
    //! @param[out] value Receives a new reader object on success, which the
    //! caller is responsible for disposing of.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an object. A new reader for the object was created,
    //! a pointer to which was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an object.
    virtual bool tryReadNext(IObjectReader *&value) = 0;

    //! @brief Attempts to read the next element as a nested array.
    //! @param[out] value Receives a new reader object on success, which the
    //! caller is responsible for disposing of.
    //! @retval true There was an element left to read and it could be
    //! interpreted as an array. A new reader for the array was created,
    //! a pointer to which was written to @p value.
    //! @retval false Either there were no more values in the array to read,
    //! or the next value could not be interpreted as an array.
    virtual bool tryReadNext(IArrayReader *&value) = 0;
};

//! @brief An interface to an object which can be used to serialize the
//! elements of an array.
class IArrayWriter
{
protected:
    // Construction/Destruction
    IArrayWriter() = default;
public:
    virtual ~IArrayWriter() = default;

    // Accessors

    // Operations

    //! @brief Writes a boolean value to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(bool value) = 0;

    //! @brief Writes a signed 8-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(int8_t value) = 0;

    //! @brief Writes an unsigned 8-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(uint8_t value) = 0;

    //! @brief Writes a signed 16-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(int16_t value) = 0;

    //! @brief Writes an unsigned 16-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(uint16_t value) = 0;

    //! @brief Writes a signed 32-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(int32_t value) = 0;

    //! @brief Writes an unsigned 32-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(uint32_t value) = 0;

    //! @brief Writes a signed 64-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(int64_t value) = 0;

    //! @brief Writes an unsigned 64-bit integer to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(uint64_t value) = 0;

    //! @brief Writes a Unicode character to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(char32_t value) = 0;

    //! @brief Writes a 32-bit floating point value to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(float value) = 0;

    //! @brief Writes a 64-bit floating point value to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(double value) = 0;

    //! @brief Writes a string value to the collection.
    //! @param[in] value The value of the string to write.
    virtual void write(string_cref_t value) = 0;

    //! @brief Writes a block of bytes to the collection.
    //! @param[in] value A pointer to the first byte to write.
    //! @param[in] byteCount The count of bytes pointed to by @p value.
    virtual void write(const void *value, size_t byteCount) =0;

    //! @brief Creates a stream to allow a block of bytes to be written to
    //! the collection.
    //! @return An IStream implementation which the caller is responsible
    //! for disposing of, and must be disposed of before any more elements are
    //! written to the current array.
    virtual IStreamUPtr beginWriteBytes() =0;

    //! @brief Begins writing a nested object.
    //! @return A pointer to an object used to write the nested object which
    //! the caller is responsible for disposing of, and must be disposed of
    //! before any more elements are written to the current array.
    virtual IObjectWriter *beginWriteObject() = 0;

    //! @brief Begins writing a nested array.
    //! @return A pointer to an object used to write the nested array which
    //! the caller is responsible for disposing of, and must be disposed of
    //! before any more elements are written to the current array.
    virtual IArrayWriter *beginWriteArray() = 0;
};

//! @brief An interface to an object which provides the root of a
//! serialized hierarchy.
class HierarchyRootPrivate : public SharedVirtualBase
{
protected:
    // Construction/Destruction
    HierarchyRootPrivate() = default;
public:
    virtual ~HierarchyRootPrivate() = default;

    // Overrides
    virtual bool hasRootObject() const = 0;
    virtual bool hasRootArray() const = 0;
    virtual IObjectReader *getRootObject() = 0;
    virtual IArrayReader *getRootArray() = 0;
};

using HierarchyRootPrivateSPtr = std::shared_ptr<HierarchyRootPrivate>;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
