//! @file ObjectGL/VertexSchema.cpp
//! @brief The definition of an object which describes the format of an
//! OpenGL vertex buffer resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Core/Version.hpp"
#include "Ag/ObjectGL/CommandSets.hpp"
#include "CommandSetTools.hpp"
#include "Ag/ObjectGL/VertexSchema.hpp"
#include "Ag/ObjectGL/Program.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
enum class DataTypeClass : uint8_t
{
    None,
    Conventional,
    Integer,
    Double,

};

struct VertexAttribTypeInfo
{
    AttribType ID;
    DataTypeClass TypeClass;
    uint8_t Size;
    bool IsNormalised;
    VertexAttribPointerType BaseType;
    Ag::Version MinVersion;
    const char *Name;

    VertexAttribTypeInfo() :
        ID(AttribType::Max),
        TypeClass(DataTypeClass::None),
        Size(0),
        IsNormalised(false),
        BaseType(gl::VertexAttribPointerType::Byte),
        Name("(unknown)")
    {
    }

    VertexAttribTypeInfo(AttribType id, DataTypeClass typeClass,
                            size_t byteCount, bool isNormalised,
                            VertexAttribPointerType baseType,
                            const char *displayName,
                            Ag::Version minVersion = Ag::Version(0, 0, 0, 0)) :
        ID(id),
        TypeClass(typeClass),
        Size(static_cast<uint8_t>(byteCount)),
        IsNormalised(isNormalised),
        BaseType(baseType),
        MinVersion(minVersion),
        Name(displayName)
    {
    }
};

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
const VertexAttribTypeInfo *getTypeInfo(AttribType id)
{
    static const VertexAttribTypeInfo types[] = {
        { AttribType::Int8,                        DataTypeClass::Integer,      1, false, VertexAttribPointerType::Byte, "8-bit signed integer", Ag::Version(3)}, // OpenGL 3.0+
        { AttribType::Int8Norm,                    DataTypeClass::Conventional, 1, true,  VertexAttribPointerType::Byte, "8-bit normalised signed integer" },
        { AttribType::Uint8,                       DataTypeClass::Integer,      1, false, VertexAttribPointerType::UnsignedByte, "8-bit unsigned integer", Ag::Version(3) },  // OpenGL 3.0+
        { AttribType::Uint8Norm,                   DataTypeClass::Conventional, 1, true,  VertexAttribPointerType::UnsignedByte, "8-bit normalised unsigned integer" },
        { AttribType::Int16,                       DataTypeClass::Integer,      2, false, VertexAttribPointerType::Short, "16-bit signed integer", Ag::Version(3) }, // OpenGL 3.0+
        { AttribType::Int16Norm,                   DataTypeClass::Conventional, 2, true,  VertexAttribPointerType::Short, "16-bit normalised signed integer" },
        { AttribType::Uint16,                      DataTypeClass::Integer,      2, false, VertexAttribPointerType::UnsignedShort, "8-bit unsigned integer", Ag::Version(3) }, // OpenGL 3.0+
        { AttribType::Uint16Norm,                  DataTypeClass::Conventional, 2, true,  VertexAttribPointerType::UnsignedShort, "16-bit normalised unsigned integer" },
        { AttribType::Int32,                       DataTypeClass::Integer,      4, false, VertexAttribPointerType::Int, "32-bit signed integer", Ag::Version(3) }, // OpenGL 3.0+
        { AttribType::Int32Norm,                   DataTypeClass::Conventional, 4, true,  VertexAttribPointerType::Int, "32-bit normalised signed integer" },
        { AttribType::Uint32,                      DataTypeClass::Integer,      4, false, VertexAttribPointerType::UnsignedInt, "32-bit normalised unsigned integer", Ag::Version(3) }, // OpenGL 3.0+
        { AttribType::Uint32Norm,                  DataTypeClass::Conventional, 4, true,  VertexAttribPointerType::UnsignedInt, "32-bit unsigned integer" },
        { AttribType::Float,                       DataTypeClass::Conventional, 4, false, VertexAttribPointerType::Float, "32-bit floating point" },
        { AttribType::HalfFloat,                   DataTypeClass::Conventional, 2, false, VertexAttribPointerType::HalfFloat, "16-bit floating point" },
        { AttribType::Double,                      DataTypeClass::Double,       8, false, VertexAttribPointerType::Double, "64-bit floating point", Ag::Version(4,1) }, // OpenGL 4.1+
        { AttribType::Fixed,                       DataTypeClass::Conventional, 4, false, VertexAttribPointerType::Fixed, "32-bit fixed point", Ag::Version(3) }, // OpenGL 3.0+
        { AttribType::IntTriple_2_10_10_10Norm,    DataTypeClass::Conventional, 4, true,  VertexAttribPointerType::Int2_10_10_10_Rev, "32-bit signed packed colour quad" },
        { AttribType::UintTriple_2_10_10_10Norm,   DataTypeClass::Conventional, 4, true,  VertexAttribPointerType::UnsignedInt2_10_10_10_Rev, "32-bit unsigned packed colour quad" },
        { AttribType::UintTriple_10F_11F_11FNorm,  DataTypeClass::Conventional, 4, true,  VertexAttribPointerType::UnsignedInt10F_11F_11F_Rev, "32-bit floating point packed colour triplet", Ag::Version(4, 4) },
        {} // Max
    };

    return types + std::underlying_type_t<AttribType>(std::min(id, AttribType::Max));
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// VertexElement Member Definitions
////////////////////////////////////////////////////////////////////////////////
VertexAttrib::VertexAttrib(const std::string_view &name,
                           AttribType dataType, size_t offset,
                           int elementCount /*= -1*/) :
    _name(name),
    _offset(static_cast<uint32_t>(offset)),
    _dataType(dataType),
    _dataTypeInfo(getTypeInfo(dataType)),
    _elementCount(std::clamp<uint8_t>(static_cast<uint8_t>(elementCount), 1, 4))
{
    if (elementCount < 0)
    {
        switch (_dataTypeInfo->BaseType)
        {
        case VertexAttribPointerType::UnsignedByte:
        case VertexAttribPointerType::Int2_10_10_10_Rev:
        case VertexAttribPointerType::UnsignedInt10F_11F_11F_Rev:
            _elementCount = 0; // A synonym for GL_BGRA
            break;

        default:
            throw Ag::NotSupportedException("A non-integer vertex attribute with "
                                            "GL_BGRA elements");
        }
    }
}

Ag::string_cref_t VertexAttrib::getName() const { return _name; }
AttribType VertexAttrib::getDataType() const { return _dataType; }
uint32_t VertexAttrib::getOffset() const { return _offset; }

//! @brief Calculates the total size of the element in bytes.
uint32_t VertexAttrib::getTotalSize() const
{
    return _dataTypeInfo->Size * getElementCount();
}

//! @brief Gets the count of element in the attribute.
//! @return The element count or 0 as a synonym for GL_BGRA.
uint8_t VertexAttrib::getElementCount() const
{
    // 0 has the special meaning of GL_BGRA when used with a packed
    // 32-bit element.
    return (_elementCount == 0) ? 1 : _elementCount;
}

//! @brief Indicates whether the attribute should be normalised to a range
//! of 0.0 to 1.0 or -1.0 to 1.0 depending on signedness.
bool VertexAttrib::isNormalised() const { return _dataTypeInfo->IsNormalised; }

//! @brief Describes the vertex attribute to the current OpenGL context.
//! @param[in] api The OpenGL API appropriate to the current context.
//! @param[in] attributeId The numeric identifier of the attribute within the
//! vertex shader program to which the current attribute should be bound.
//! @param[in] vertexSize The total size of the overall vertex, in bytes.
void VertexAttrib::define(const GLAPI &api, uint32_t attributeId, size_t vertexSize) const
{
    // Call VertexAttribPointer() or the like to register the vertex attribute.
    if (api.getAPIVersion() < _dataTypeInfo->MinVersion)
    {
        std::string message("A vertex element of type ");
        message.append(_dataTypeInfo->Name);

        throw Ag::NotSupportedException(message.c_str());
    }

    GLint elementCount = (_elementCount == 0) ? Ag::toScalar(gl::PixelFormat::BGRA) :
                                                _elementCount;

    // This is so that the pointer parameter in vertexAttrib*Pointer() can
    // actually be an offset with a minimum of messing around.
    const uint8_t *vertexStart = nullptr;

    switch (_dataTypeInfo->TypeClass)
    {
    case DataTypeClass::Conventional:
        api.vertexAttribPointer(attributeId, elementCount,
                                _dataTypeInfo->BaseType,
                                toBoolean(_dataTypeInfo->IsNormalised),
                                static_cast<GLsizei>(vertexSize),
                                vertexStart + _offset);
        break;

    case DataTypeClass::Integer:
        api.vertexAttribIPointer(attributeId, elementCount,
                                 convertEnum<gl::VertexAttribIType>(_dataTypeInfo->BaseType),
                                 static_cast<GLsizei>(vertexSize),
                                 vertexStart + _offset);
        break;

    case DataTypeClass::Double:
        api.vertexAttribLPointer(attributeId, elementCount,
                                 convertEnum<gl::VertexAttribLType>(_dataTypeInfo->BaseType),
                                 static_cast<GLsizei>(vertexSize),
                                 vertexStart + _offset);
        break;

    case DataTypeClass::None:
    default: {
        std::string message("The data type of vertex attribute '");
        appendAgString(message, _name);
        message.push_back('\'');

        throw Ag::NotSupportedException(message.c_str());
    } break;

    }
}

////////////////////////////////////////////////////////////////////////////////
// VertexSchema Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty vertex schema.
VertexSchema::VertexSchema() :
    _stride(0)
{
}

//! @brief Constructs an immutable definition of the structure of a vertex.
//! @param[in] attributes The set of attributes in the vertex type.
//! @param[in] preferredStride The total size of the vertex, in bytes, if it
//! cannot be inferred from the attributes.
VertexSchema::VertexSchema(const VertexAttribCollection &attributes,
                           size_t preferredStride /*= 0*/) :
    _attributes(attributes),
    _stride(0)
{
    uint32_t totalSize = 0;

    for (size_t i = 0, c = _attributes.size(); i < c; ++i)
    {
        const VertexAttrib &attrib = _attributes[i];

        totalSize = std::max(attrib.getOffset() + attrib.getTotalSize(),
                             totalSize);

        auto result = _nameIndex.try_emplace(attrib.getName(), i);

        if (result.second == false)
        {
            std::string message("Vertex attribute '");
            appendAgString(message, attrib.getName());
            message.append("' is defined more than once.");

            throw Ag::OperationException(message.c_str());
        }
    }

    _stride = std::max<size_t>(preferredStride, totalSize);
}

//! @brief Determines if any attributes are defined in the vertex schema.
//! @retval true At least one vertex attribute is defined.
//! @retval false No vertex attributes are defined.
bool VertexSchema::isEmpty() const
{
    return _attributes.empty();
}

//! @brief Gets the total size of the vertex structure, in bytes.
size_t VertexSchema::getVertexSize() const noexcept
{
    return _stride;
}

//! @brief Gets the count of vertex attributes defined by the schema.
size_t VertexSchema::getAttributeCount() const noexcept
{
    return _attributes.size();
}

//! @brief Attempts to look up the index of a vertex attribute from its name.
//! @param[in] name The name to look up.
//! @param[out] index Receives the internal index of the attribute.
//! @retval true A matching attribute was found and its index returned.
//! @retval false The schema didn't contain an attribute with a matching name.
bool VertexSchema::tryFindAttributeByName(Ag::string_cref_t name,
                                          size_t &index) const
{
    auto pos = _nameIndex.find(name);

    if (pos == _nameIndex.end())
    {
        index = _attributes.size();
        return false;
    }
    else
    {
        index = pos->second;
        return true;
    }
}

//! @brief Gets the attribute at the specified index.
//! @param[in] index The 0-based index of the attribute to obtain.
//! @return A read-only reference to the attribute.
const VertexAttrib &VertexSchema::operator[](size_t index) const
{
    return _attributes[index];
}

////////////////////////////////////////////////////////////////////////////////
// VertexSchemaBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which can be used to incrementally define the
//! structure and format of a vertex.
VertexSchemaBuilder::VertexSchemaBuilder() :
    _preferredSize(0)
{
    _attributes.reserve(16);
}

//! @brief Sets the preferred size of the vertex.
//! @param[in] byteCount The stride between successive vertex structures. A
//! value of 0 indicates that size should be calculated from the vertex
//! attributes.
void VertexSchemaBuilder::setVertexSize(size_t byteCount)
{
    _preferredSize = byteCount;
}

//! @brief Resets the object to an empty state.
void VertexSchemaBuilder::clear()
{
    _attributes.clear();
    _preferredSize = 0;
}

//! @brief Adds a 2-dimensional position attribute using 32-bit floating point values.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
void VertexSchemaBuilder::add2DPosition(const std::string_view &name, size_t offset)
{
    _attributes.emplace_back(name, AttribType::Float, offset, 2);
}

//! @brief Adds a 3-dimensional position attribute using 32-bit floating point values.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
void VertexSchemaBuilder::add3DPosition(const std::string_view &name, size_t offset)
{
    _attributes.emplace_back(name, AttribType::Float, offset, 3);
}

//! @brief Adds a 4-dimensional position attribute using 32-bit floating point values.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
void VertexSchemaBuilder::add4DPosition(const std::string_view &name, size_t offset)
{
    _attributes.emplace_back(name, AttribType::Float, offset, 4);
}

//! @brief Adds an RGB colour attribute using three 32-bit floating point values.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
void VertexSchemaBuilder::addHDRColour(const std::string_view &name, size_t offset)
{
    _attributes.emplace_back(name, AttribType::Float, offset, 3);
}

//! @brief Adds an RGBA colour attribute using four 32-bit floating point values.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
void VertexSchemaBuilder::addHDRColourWithAlpha(const std::string_view &name, size_t offset)
{
    _attributes.emplace_back(name, AttribType::Float, offset, 4);
}

//! @brief Adds an RGBA colour attribute using four normalised unsigned 8-bit
//! integers packed into a single 32-bit attribute.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
void VertexSchemaBuilder::addPackedIntegerColour(const std::string_view &name, size_t offset)
{
    _attributes.emplace_back(name, AttribType::Uint8Norm, offset, 4);
}

//! @brief Adds a custom attribute.
//! @param[in] name The unique name of the attribute to add.
//! @param[in] dataType The data type of the most basic element of the attribute.
//! @param[in] offset The offset of the attribute within the vertex structure
//! measured in bytes.
//! @param[in] elementCount The count of elements of the specified type in the
//! attribute or -1 to specify the special GL_BGRA mode for packed colours.
void VertexSchemaBuilder::addAttribute(const std::string_view &name,
                                       AttribType dataType, size_t offset,
                                       int elementCount /*= -1*/)
{
    _attributes.emplace_back(name, dataType, offset, elementCount);
}

//! @brief Creates an immutable vertex schema from the current state of the
//! builder object.
VertexSchema VertexSchemaBuilder::createSchema()
{
    return VertexSchema(_attributes, _preferredSize);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

