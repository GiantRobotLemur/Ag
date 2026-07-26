//! @file IO/Exceptions.cpp
//! @brief The definition of various IO-related exception objects.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/Exceptions.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// IOException Member Definitions
////////////////////////////////////////////////////////////////////////////////
utf8_cptr_t IOException::Domain = "IOException";

//! @brief Constructs an exception thrown when the mechanism of transferring
//! data to or from an IO device failed.
//! @param[in] detail The detail of the specific instance of the failure.
IOException::IOException(const std::string_view &detail)
{
    initialise(Domain, "The program failed in its attempt to read or "
               "write data to a device.",
               detail);
}

////////////////////////////////////////////////////////////////////////////////
// DataFormatException Member Definitions
////////////////////////////////////////////////////////////////////////////////
utf8_cptr_t DataFormatException::Domain = "DataFormatException";

//! @brief Constructs an exception thrown when the mechanism of transferring
//! data to or from an IO device failed.
//! @param[in] detail The detail of the specific instance of the failure.
DataFormatException::DataFormatException(const std::string_view &detail)
{
    initialise(Domain,
               "Data read from an device was not in the expected format.",
               detail);
}

////////////////////////////////////////////////////////////////////////////////
// PropertyNotFoundException Member Definitions
////////////////////////////////////////////////////////////////////////////////
utf8_cptr_t PropertyNotFoundException::Domain = "PropertyNotFoundException";

//! @brief Constructs an exception detailing that the program tried to access a
//! serialized property which was not present.
//! @param[in] propertyName The name of the property which was missing.
PropertyNotFoundException::PropertyNotFoundException(string_cref_t propertyName)
{
    std::string detail("The property '");
    appendAgString(detail, propertyName);;
    detail.append("' was not found in a serialized object.");

    initialise(Domain,
               "A property could not be found in a serialized object.",
               detail);
}

////////////////////////////////////////////////////////////////////////////////
// PropertyTypeException Member Definitions
////////////////////////////////////////////////////////////////////////////////
utf8_cptr_t PropertyTypeException::Domain = "PropertyTypeException";

//! @brief Constructs an exception thrown when the program attempts to interpret
//! a serialized object property as an incompatible data type.
//! @param[in] propertyName The name of the property being accessed.
//! @param[in] requestedType The data type requested.
PropertyTypeException::PropertyTypeException(string_cref_t propertyName,
                                             const std::string_view &requestedType)
{
    std::string detail;
    detail.reserve(64 + propertyName.getUtf8Length() + requestedType.length());

    detail.assign("The property '");
    appendAgString(detail, propertyName);
    detail.append("' could not be interpreted as a ");
    detail.append(requestedType);
    detail.append("' data type.");

    initialise(Domain, "A serialized object property could not be interpreted "
               "as the required data type.", detail);
}

//! @brief Constructs an exception thrown when the program attempts to interpret
//! a serialized array element as an incompatible data type.
//! @param[in] requestedType The data type requested.
PropertyTypeException::PropertyTypeException(const std::string_view &requestedType)
{
    std::string detail;
    detail.reserve(64 + requestedType.length());

    detail.assign("An array element could not be interpreted as a '");
    detail.append(requestedType);
    detail.append("' data type.");

    initialise(Domain, "A serialized array element could not be interpreted "
               "as the required data type.", detail);
}

////////////////////////////////////////////////////////////////////////////////
// FieldTooBigException Member Definitions
////////////////////////////////////////////////////////////////////////////////
utf8_cptr_t FieldTooBigException::Domain = "FieldTooBigException";

//! @brief Constructs an exception thrown when the program attempts to access
//! a large byte block field as a linear block.
//! @param[in] blockSize The actual size of the field block.
FieldTooBigException::FieldTooBigException(StreamLength blockSize)
{
    std::string detail;
    detail.reserve(128);

    detail.assign("The program attempted to access a byte block field of ");
    Ag::appendFileSize(FormatInfo::getDisplay(), detail, static_cast<uint64_t>(blockSize));
    detail.append(" as a single unit.");

    initialise(Domain, "The program attempted to access a byte "
               "block field which was too large", detail);
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

