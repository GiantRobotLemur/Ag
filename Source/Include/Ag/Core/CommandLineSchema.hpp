//! @file CommandLineSchema.hpp
//! @brief The declaration of an object which defines which command line options
//! are valid.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2023
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_COMMAND_LINE_SCHEMA_HPP__
#define __AG_CORE_COMMAND_LINE_SCHEMA_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <memory>

#include "Configuration.hpp"
#include "EnumInfo.hpp"
#include "String.hpp"

namespace Ag {

//! @brief A namespace containing command line manipulation tools.
namespace Cli {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Defines the requirement for a value following a command line
//! option argument.
enum class OptionValue
{
    //! @brief The option should have no bound argument value.
    None,

    //! @brief The option may have a bound argument value.
    Optional,

    //! @brief The option must be followed by an argument value.
    Mandatory,
};

//! @brief Specifies the required multiplicity of command line arguments not
//! bound to an option, i.e. unbound arguments.
enum ValueMultiplicity
{
    //! @brief Indicates unbound arguments are invalid.
    None,

    //! @brief Indicates zero or one unbound arguments are allowed.
    UpToOne,

    //! @brief Indicates exactly one unbound argument is required.
    ExactlyOne,

    //! @brief Indicate one or more unbound arguments are required.
    AtLeastOne,

    //! @brief Indicate zero or more unbound arguments are allowed.
    Many,
};

//! @brief Defines a command line parameter, though not how it is expressed.
class OptionDefinition
{
public:
    // Construction
    OptionDefinition();
    OptionDefinition(uint32_t id, string_cref_t description,
                     string_cref_t valueName = String::Empty,
                     OptionValue valueRequired = OptionValue::None);

    // Accessors
    uint32_t getId() const;
    string_cref_t getDescription() const;
    OptionValue getValueRequired() const;
    string_cref_t getValueName() const;
private:
    // Internal Fields
    uint32_t _id;
    OptionValue _valueRequirement;
    String _description;
    String _valueName;
};

class SchemaBuilder;
class SchemaPrivate;
class SchemaBuilderPrivate;

//! @brief An object defining all valid command line options.
class Schema
{
public:
    Schema(const SchemaBuilderPrivate &builder);
    ~Schema() = default;

    // Accessors
    ValueMultiplicity getValueMultiplicity() const;
    bool tryFindShortOption(char32_t shortOption, size_t &index) const;
    bool tryFindLongOption(const String &option, size_t &index) const;

    const OptionDefinition &getOptionDefinition(size_t index) const;

    String getHelpText(int maxWidth = -1) const;
private:
    // Internal Fields
    std::shared_ptr<SchemaPrivate> _schema;
};

//! @brief An object used to construct an immutable command line option schema.
class SchemaBuilder
{
public:
    // Construction
    SchemaBuilder();

    // Accessors
    void setName(const std::string_view &name);
    void setDescription(const std::string_view &description);

    // Operations
    void defineValueArgument(utf8_cptr_t name, ValueMultiplicity multiplicity);
    void defineOption(uint32_t id, utf8_cptr_t description,
                      OptionValue value = OptionValue::None,
                      utf8_cptr_t valueName = nullptr);
    void defineAlias(uint32_t id, char32_t shortForm, bool isCaseSensitve = true);
    void defineAlias(uint32_t id, utf8_cptr_t longForm, bool isCaseSensitive = true);

    Schema createSchema() const;
private:
    // Internal Fields
    std::shared_ptr<SchemaBuilderPrivate> _builder;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief A useful function for creating descriptions for enumeration-based
//! command line option values.
//! @tparam TEnum The data type of the described enumeration which can be
//! inferred from the typeInfo argument.
//! @tparam TEnumSym The data type of the object which describes each
//! enumeration symbol, also inferred from the typeInfo argument.
//! @param[out] buffer The UTF-8 encoded string to append the description to.
//! @param[in] typeInfo The enum type metadata containing the descriptions to
//! extract.
template<typename TEnum, typename TEnumSym>
static void appendValidValues(std::string &buffer,
                              const EnumInfo<TEnum, TEnumSym> &typeInfo)
{
    const auto &symbols = typeInfo.getSymbols();

    if (symbols.size() == 1)
    {
        buffer.append("The only valid value is ");
        buffer.append(symbols.front().getSymbol());
        buffer.push_back('.');
    }
    else if (symbols.size() > 1)
    {
        size_t lastSymbol = symbols.size() - 1;

        buffer.append("Valid values are ");

        for (size_t i = 0; i < lastSymbol; ++i)
        {
            if (i > 0)
            {
                buffer.push_back(',');
                buffer.push_back(' ');
            }

            buffer.append(symbols[i].getSymbol());
        }

        buffer.append(" and ");
        buffer.append(symbols.back().getSymbol());
        buffer.push_back('.');
    }
}

}} // namespace Ag::Cli

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
