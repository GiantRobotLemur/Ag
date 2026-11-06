//! @file Ag/Text/ParseMessage.hpp
//! @brief The declaration of objects which allow messages to be generated from
//! the parsing process.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_PARSE_MESSAGE_HPP__
#define _AG_TEXT_PARSE_MESSAGE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>

#include "CharacterAnalyser.hpp"

namespace Ag {
namespace Text {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
enum class Severity
{
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
};

using SeverityEnumInfo = Ag::EnumInfo<Severity>;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A message generated from the parsing process.
class Message
{
public:
    // Construction/Destruction
    Message();
    Message(Severity severity, const SourceReference &location, string_cref_t message);
    ~Message() = default;

    // Accessors
    const SourceReference &getLocation() const noexcept;
    string_cref_t getMessage() const noexcept;
    Severity getSeverity() const noexcept;

private:
    // Internal Fields
    SourceReference _location;
    String _message;
    Severity _severity;
};

//! @brief A collection of messages.
class Messages
{
public:
    // Public Types
    using MessageCollection = std::deque<Message>;
    using Iterator = MessageCollection::const_iterator;

    // Construction/Destruction
    Messages();
    ~Messages() = default;

    // Accessors
    bool isEmpty() const;
    bool hasErrors() const;
    Iterator begin() const;
    Iterator end() const;

    // Operations
    void clear();
    void log(const SourceReference &location, Severity severity, string_cref_t text);
    void log(const SourceReference &location, Severity severity, std::string &text);
    void log(const SourceReference &location, Severity severity, utf8_cptr_t text);
    void log(const SourceReference &location, Severity severity, utf8_cptr_t text, const Ag::VariantList &values);
private:
    // Internal Fields
    MessageCollection _messages;
    bool _hasErrors;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
const SeverityEnumInfo &getSeverityMetadata();


////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
