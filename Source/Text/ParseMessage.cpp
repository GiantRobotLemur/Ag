//! @file Text/ParseMessage.cpp
//! @brief The definition of objects which allow messages to be generated from
//! the parsing process.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Text/ParseMessage.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#define STATIC_SCALAR_CLASS_DEF23(t, x, y) Ag::EnumSymbol<t>(t ## :: ## x, # x, # x , y)

namespace Ag {
namespace Text {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Message Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty message object.
Message::Message() :
    _severity(Severity::Debug)
{
}

//! @brief Constructs a populated message.
//! @param[in] severity Specifies the severity of the message.
//! @param[in] location The location within the parsed source text the message
//! references.
//! @param[in] message The text detailing the message contents.
Message::Message(Severity severity, const SourceReference &location,
                 string_cref_t message) :
    _location(location),
    _message(message),
    _severity(severity)
{
}

//! @brief Gets the location in the parsed source text associated with
//! the message.
const SourceReference &Message::getLocation() const noexcept
{
    return _location;
}

//! @brief Gets the message text.
string_cref_t Message::getMessage() const noexcept
{
    return _message;
}

//! @brief Gets the severity of the issue documented by the message.
Severity Message::getSeverity() const noexcept
{
    return _severity;
}

////////////////////////////////////////////////////////////////////////////////
// Messages Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a new collection of messages.
Messages::Messages() :
    _hasErrors(false)
{
}

//! @brief Determines whether the collection contains no elements.
//! @retval true The collection contains zero elements.
//! @retval false The collection contains at least one element.
bool Messages::isEmpty() const
{
    return _messages.empty();
}

//! @brief Determines whether the collection contains any errors.
//! @retval true The collection contains at least one message marked as Error or Fatal.
//! @retval false The collection contains no messages marked as Error or Fatal.
bool Messages::hasErrors() const
{
    return _hasErrors;
}

//! @brief Gets an iterator pointing to the first message of the collection.
Messages::Iterator Messages::begin() const
{
    return _messages.begin();
}

//! @brief Gets an iterator positioned after the last message of the collection.
Messages::Iterator Messages::end() const
{
    return _messages.end();
}

//! @brief Removes all messages from the collection.
void Messages::clear()
{
    _messages.clear();
    _hasErrors = false;
}

//! @brief Adds a message to the collection.
//! @param[in] location The location in the parsed text the message references.
//! @param[in] severity The severity associated with the message.
//! @param[in] text The text of the message to add.
void Messages::log(const SourceReference &location, Severity severity, string_cref_t text)
{
    _hasErrors |= (severity >= Severity::Error);

    _messages.emplace_back(severity, location, text);
}

//! @brief Adds a message to the collection.
//! @param[in] location The location in the parsed text the message references.
//! @param[in] severity The severity associated with the message.
//! @param[in] text The text of the message to add.
void Messages::log(const SourceReference &location, Severity severity, std::string &text)
{
    String immutableText(text);

    log(location, severity, immutableText);
}

//! @brief Adds a message to the collection.
//! @param[in] location The location in the parsed text the message references.
//! @param[in] severity The severity associated with the message.
//! @param[in] text The text of the message to add.
void Messages::log(const SourceReference &location, Severity severity, utf8_cptr_t text)
{
    String immutableText(text);

    log(location, severity, immutableText);
}

//! @brief Adds a message to the collection.
//! @param[in] location The location in the parsed text the message references.
//! @param[in] severity The severity associated with the message.
//! @param[in] formatSpec The format specification to process in order to
//! generate formatted message text.
//! @param[in] values The values to insert into the message text.
void Messages::log(const SourceReference &location, Severity severity,
                   utf8_cptr_t formatSpec, const Ag::VariantList &values)
{
    std::string formattedText;
    FormatInfo format(FormatInfo::getDisplay());

    Ag::appendFormat(formatSpec, formattedText, values);

    log(location, severity, formattedText);
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Provides metadata for the Severity enumeration type.
const SeverityEnumInfo &getSeverityMetadata()
{
    static const SeverityEnumInfo metadata({
        STATIC_SCALAR_CLASS_DEF23(Severity, Debug, "Messages intended for parser development."),
        STATIC_SCALAR_CLASS_DEF23(Severity, Info, "Messages intended to inform."),
        STATIC_SCALAR_CLASS_DEF23(Severity, Warning, "Messages indicating a possible error."),
        STATIC_SCALAR_CLASS_DEF23(Severity, Error, "Messages indicating an error which prevents post-parsing steps."),
        STATIC_SCALAR_CLASS_DEF3(Severity, Fatal, "Fatal Error", "Messages indicating an error which stops parsing."),
    });

    return metadata;
}

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////

