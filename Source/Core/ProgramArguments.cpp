//! @file Core/ProgramArguments.cpp
//! @brief The definition of an object which manages command line argument
//! parsing, processing and verification.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cwchar>
#include <cwctype>
#include <deque>
#include <map>
#include <unordered_map>
#include <string_view>

#include "CoreInternal.hpp"
#include "Ag/Core/App.hpp"
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Format.hpp"
#include "Ag/Core/ProgramArguments.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Core/Variant.hpp"

namespace Ag {
namespace Cli {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing an argument token, possibly with an associated value.
struct ArgumentToken
{
    //! @brief Species the type of command line element a token represents.
    enum Type
    {
        //! @brief The token is an unadorned argument.
        Argument,

        //! @brief The token is an option defined by a single character, possibly
        //! as part of a group.
        ShortOption,

        //! @brief The token is a multi-character option.
        LongOption,

        //! @brief The token is a single or multi-character option, but only
        //! expressed on a Win32 command line.
        Win32Option,
    };

    String Original;
    String Token;
    String Value;
    Type ArgumentType;
    bool HasValue;

    //! @brief Constructs an argument token.
    //! @param[in] arg The text of the argument.
    ArgumentToken(const String &arg) :
        Original(arg),
        Token(arg),
        ArgumentType(Argument),
        HasValue(false)
    {
    }

    //! @brief Constructs an option token with no associated value.
    //! @param[in] argType The type of option expressed.
    //! @param[in] original The original argument for output in messages.
    //! @param[in] option The option identifier.
    ArgumentToken(Type argType, const String &original, const String &option) :
        Original(original),
        Token(option),
        ArgumentType(argType),
        HasValue(false)
    {
    }

    //! @brief Constructs an option token with an associated value.
    //! @param[in] argType The type of option expressed.
    //! @param[in] option The option identifier.
    //! @param[in] value The value explicitly associated with the option
    ArgumentToken(Type argType, const String &original,
                  const String &option, const String &value) :
        Original(original),
        Token(option),
        Value(value),
        ArgumentType(argType),
        HasValue(true)
    {
    }
};

//! @brief A collection of ArgumentToken objects.
class ArgumentCollection : public std::deque<ArgumentToken> {};

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
//! @brief Gets the file name of the main application module for when it is not
//! included in the command line arguments.
String getProgramFileName()
{
    return getModuleFileName(reinterpret_cast<uintptr_t>(::GetModuleHandleW(nullptr)));
}
#endif

//! @brief Attempts to append one or more argument tokens to a collection.
//! @param[out] argToken The collection to receive the tokens.
//! @param[in] arg The command line argument token.
//! @param[out] error Receives a message if processing failed.
//! @retval true Tokens were added to the collection.
//! @retval false The argument was invalid, error is updated to describe why.
bool tryAppendArgument(ArgumentCollection &argTokens,
                       const String &arg, String &error)
{
    bool isOK = false;
    auto iter = arg.begin();
    auto startIter = iter;

    if (iter == arg.end())
    {
        // This is an internal error, not bad user input.
        throw OperationException(std::string_view("Command line argument tokens cannot be empty."));
    }
    else
    {
        if (*iter == U'-')
        {
            // Move past the first character.
            ++iter;

            if ((iter != arg.end()) &&
                (*iter == U'-'))
            {
                // Move past the second character to extract the long option.
                ++iter;

                auto equalsPos = arg.find(iter, U'=');

                if (equalsPos == arg.end())
                {
                    // There is value bound to the option.
                    String original = arg;
                    String option = arg.substring(iter, arg.end());

                    if (option.isEmpty() == false)
                    {
                        // There is no assigned option value.
                        argTokens.emplace_back(ArgumentToken::LongOption,
                                               original, option);
                        isOK = true;
                    }
                }
                else
                {
                    // There is an assigned option.
                    String original = arg.substring(startIter, equalsPos);
                    String option = arg.substring(iter, equalsPos);
                    ++equalsPos;
                    String value = arg.substring(equalsPos, arg.end());

                    if ((option.isEmpty() == false) && (value.isEmpty() == false))
                    {
                        argTokens.emplace_back(ArgumentToken::LongOption,
                                               original, option, value);
                        isOK = true;
                    }
                }
            }
            else
            {
                // Its zero or more a short options.
                while (iter != arg.end())
                {
                    if (*iter == U'=')
                    {
                        // We have a value associated with the last option.
                        if (isOK)
                        {
                            // Associate the value with the previous option token.
                            ++iter;
                            ArgumentToken &previous = argTokens.back();
                            previous.Value = arg.substring(iter, arg.end());
                            previous.HasValue = true;
                        }

                        // Exit the loop.
                        iter = arg.end();
                    }
                    else
                    {
                        char32_t originalArray[2];

                        originalArray[0] = U'-';
                        originalArray[1] = *iter;

                        String original(originalArray, 2);
                        String option(originalArray + 1, 1);

                        argTokens.emplace_back(ArgumentToken::ShortOption,
                                               original, option);
                        ++iter;
                        isOK = true;
                    }
                }
            }
        }
#ifdef _WIN32
        // The user of '/' to express a command line option is Windows-only
        // behaviour as under POSIX it would interfere with arguments which
        // express file paths.
        else if (*iter == U'/')
        {
            ++iter;

            if (iter != arg.end())
            {
                auto equalsPos = arg.find(iter, U'=');

                if (equalsPos == arg.end())
                {
                    // There is no associated value.
                    String original = arg;

                    argTokens.emplace_back(ArgumentToken::Win32Option, original,
                                           arg.substring(iter, arg.end()));
                }
                else
                {
                    // Extract the option(s) and value.
                    String original = arg.substring(startIter, equalsPos);
                    String option = arg.substring(iter, equalsPos);
                    ++equalsPos;
                    String value = arg.substring(equalsPos, arg.end());

                    argTokens.emplace_back(ArgumentToken::Win32Option,
                                           original, option, value);
                }

                isOK = true;
            }
        }
#endif
        else
        {
            // It's a non-option argument.
            argTokens.emplace_back(arg);
            isOK = true;
        }

        if (isOK == false)
        {
            error = String::format("Argument '{0}' is malformed.", { arg });
        }
    }

    return isOK;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ProgramArguments Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object ready to process command line options.
ProgramArguments::ProgramArguments() :
    _command(NoCommand)
{
}

//! @brief Constructs an object ready to process command line options.
//! @param[in] schema The schema which defines what command line options are
//! valid.
ProgramArguments::ProgramArguments(const Schema &schema) :
    _schema(schema),
    _command(NoCommand)
{
}

//! @brief Gets the name and path of the program binary as specified at launch.
const String &ProgramArguments::getProgramFile() const
{
    return _programFile;
}

//! @brief Gets an object describing the schema of command line arguments.
const Schema &ProgramArguments::getSchema() const
{
    return _schema;
}

//! @brief Gets the numeric identifier of a command interpreted from the
//! last set of parsed command line options.
//! @return The numeric identifier of the command, either a custom value or
//! something like StandardCommands::ShowHelp.
uint32_t ProgramArguments::getCommand() const
{
    return _command;
}

//! @brief Determines if a command was set the last time command line arguments
//! were processed.
//! @retval true A command was implied.
//! @retval false No command was implied.
bool ProgramArguments::hasCommand() const
{
    return _command != StandardCommands::NoCommand;
}

//! @brief Determines whether the command required is one of the standard ones.
//! @retval true If a standard command has been selected (but not NoCommand).
//! @retval false A non-standard command has been selected, or NoCommand.
bool ProgramArguments::hasStandardCommand() const
{
    return (_command > StandardCommands::NoCommand) && (_command < StandardCommands::LastStdCommand);
}

//! @brief Parses A Win32-style continuous wide character command line.
//! @param[in] win32CommandLine The command line arguments which is not expected
//! to include the program name.
//! @param[out] error Receives a string defining why the command line was invalid
//! if processing fails.
//! @retval true The command line  was successfully processed.
//! @retval false Command line processing failed, the error string should describe
//! the exact nature of the failure.
bool ProgramArguments::tryParse(wchar_cptr_t win32CommandLine, String &error)
{
    _programFile = getProgramFileName();

    ArgumentCollection tokens;
    std::vector<wchar_t> buffer;
    bool isQuoted = false;
    wchar_t currentQuote = '\0';
    bool isOK = true;

    for (size_t index = 0; isOK && (win32CommandLine[index] != L'\0'); ++index)
    {
        wchar_t next = win32CommandLine[index];

        if (isQuoted)
        {
            if (next == currentQuote)
            {
                isQuoted = false;
                currentQuote = L'\0';
            }
            else
            {
                buffer.push_back(next);
            }
        }
        else if (next == '\"')
        {
            isQuoted = true;
            currentQuote = next;
        }
        else if (iswspace(next) == 0)
        {
            buffer.push_back(next);
        }
        else if (buffer.empty() == false)
        {
            // Process the next option.
            String argument(buffer.data(), buffer.size());
            buffer.clear();

            isOK = tryAppendArgument(tokens, argument, error);
        }
    }

    if (buffer.empty() == false)
    {
        // Process the last option.
        String argument(buffer.data(), buffer.size());
        buffer.clear();

        isOK = tryAppendArgument(tokens, argument, error);
    }

    if (isOK)
    {
        if (isQuoted)
        {
            // There was an opening quote with no matching closing quote.
            error = "Missing closing quote.";
            isOK = false;
        }
        else
        {
            // Process arguments we have parsed.
            isOK = processArgumentTokens(tokens, error);
        }
    }

    return isOK;
}

//! @brief Parses a UNIX-style command line.
//! @param[in] argc The count of command line argument tokens.
//! @param[in] argv The command line argument tokens in the native character
//! set encoding. The size of the array is given by argc and the first element
//! should be the name used to launch the program.
//! @param[out] error Receives a string defining why the command line was invalid
//! if processing fails.
//! @retval true The command line was successfully processed.
//! @retval false Command line processing failed, the error string should describe
//! the exact nature of the failure.
bool ProgramArguments::tryParse(int argc, const char * const *argv, String &error)
{
    if (argc > 0)
    {
        _programFile = String::fromNativeCodePage(argv[0]);
    }

    bool isOK = true;
    ArgumentCollection tokens;

    for (int argi = 1; isOK && (argi < argc); ++argi)
    {
        String argument = String::fromNativeCodePage(argv[argi]);

        isOK = tryAppendArgument(tokens, argument, error);
    }

    if (isOK)
    {
        // Process arguments we have parsed.
        isOK = processArgumentTokens(tokens, error);
    }

    return isOK;
}

//! @brief Parses a UNIX-style command line rendered in Unicode.
//! @param[in] argc The count of command line argument tokens.
//! @param[in] argv The command line argument tokens in the native wide character
//! set encoding. The size of the array is given by argc and the first element
//! should be the name used to launch the program.
//! @param[out] error Receives a string defining why the command line was invalid
//! if processing fails.
//! @retval true The command line was successfully processed.
//! @retval false Command line processing failed, the error string should describe
//! the exact nature of the failure.
bool ProgramArguments::tryParse(int argc, const wchar_t * const *argv, String &error)
{
    if (argc > 0)
    {
        _programFile = argv[0];
    }

    bool isOK = true;
    ArgumentCollection tokens;

    for (int argi = 1; isOK && (argi < argc); ++argi)
    {
        isOK = tryAppendArgument(tokens, argv[argi], error);
    }

    if (isOK)
    {
        // Process arguments we have parsed.
        isOK = processArgumentTokens(tokens, error);
    }

    return isOK;
}

//! @brief Outputs help to the user describing the available command line options.
void ProgramArguments::showHelp() const
{
    FILE *output = App::getConsoleOutputStream();

    String helpText = _schema.getHelpText(80);

#ifdef _WIN32
    // Output help text in Win32 as Unicode.
    auto wideHelp = helpText.toWide();

    if (output != nullptr)
    {
        fputwc(L'\n', output);
        fputws(wideHelp.c_str(), output);
    }

    if (::IsDebuggerPresent())
    {
        wideHelp.push_back(L'\n');
        ::OutputDebugStringW(wideHelp.c_str());
    }
#else
    if (output != nullptr)
    {
        fputc('\n', output);
        fputs(helpText.getUtf8Bytes(), output);
    }
#endif // ifdef _WIN32
}

//! @brief Outputs information about the program version to the user.
void ProgramArguments::showVersion() const
{
    FILE *output = App::getConsoleOutputStream();

    String versionText = _schema.getVersionText();

#ifdef _WIN32
    // Output version text in Win32 as Unicode.
    auto wideHelp = versionText.toWide();
    wideHelp.push_back(L'\n');

    if (output != nullptr)
    {
        fputwc(L'\n', output);
        fputws(wideHelp.c_str(), output);
    }

    if (::IsDebuggerPresent())
    {
        wideHelp.push_back(L'\n');
        ::OutputDebugStringW(wideHelp.c_str());
    }
#else
    if (output != nullptr)
    {
        fputc('\n', output);
        fputs(versionText.getUtf8Bytes(), output);
        fputc('\n', output);
    }
#endif // ifdef _WIN32
}

//! @brief Attempts to process any of the standard commands which the user may
//! have requested via the last set of command line arguments.
//! @retval true A command was processed, the process should exit.
//! @retval false The process should continue to perform its default command.
bool ProgramArguments::tryProcessStandardCommand() const
{
    bool commandProcessed = true;

    switch (_command)
    {
    case StandardCommands::ShowHelp:
        showHelp();
        break;

    case StandardCommands::ShowVersion:
        showVersion();
        break;

    default:
        commandProcessed = false;
        break;
    }

    return commandProcessed;
}

//! @brief Implemented in derived classes to handle an option which
//! appeared on the command line.
//! @param[in] id The numeric identifier of the option which corresponds with
//! a definition in the command line schema.
//! @param[in] original The text of the option as it was expressed on the command
//! line for reference in error messages.
//! @param[in] value The optional value associated with the option, empty if no
//! value was associated with the option.
//! @param[out] error Receives an error message if processing of the command
//! line option failed.
//! @retval true The option was successfully processed.
//! @retval false The option was invalid.
//! @note The default implementation consumes associated values if possible and
//! always returns true.
bool ProgramArguments::processOption(uint32_t id, const String & /*original*/,
                                     const String &/*value*/,
                                     String &/*error*/)
{
    switch (id)
    {
    case StandardOptions::ShowHelpOption:
        setCommand(StandardCommands::ShowHelp);
        break;

    case StandardOptions::ShowVersionOption:
        setCommand(StandardCommands::ShowVersion);
        break;
    }

    return true;
}

//! @brief A member function to be overridden by derived classes to process a
//! command line argument which isn't an option.
//! @param[in] argument The argument to process.
//! @param[out] error Receives an error message is processing fails.
//! @retval true The argument was successfully processed.
//! @retval false The argument was invalid, error should be updated with a
//! message describing why.
//! @note The default implementation performs no processing and always
//! returns true.
bool ProgramArguments::processArgument(const String & /* argument */,
                                       String & /* error */)
{
    return true;
}

//! @brief A member function to be implemented by derived classes in order
//! to validate the state of the object once all options and arguments have
//! been processed.
//! @param[out] error Receives text describing a failure if the object is in an
//! invalid state.
//! @retval true The object is in a valid state.
//! @retval false The combination of command line options and arguments
//! processed has left the object in an invalid state.
//! @note The default implementation always returns true.
bool ProgramArguments::validate(String & /* error */) const
{
    return true;
}

//! @brief Allows the accumulated command line options and arguments to be
//! processed before validation.
//! @note The default implementation performs no processing.
void ProgramArguments::postProcess()
{
}

//! @brief Resets any accumulated option values before parsing a new set
//! of command line arguments.
//! @note The default implementation should be called by derived implementations.
void ProgramArguments::clear()
{
    _command = StandardCommands::NoCommand;
}

//! @brief An internal function which allows the command line option
//! schema to be updated.
//! @param[in] schema The object used to create a new schema.
void ProgramArguments::setSchema(const SchemaBuilder &schema)
{
    _schema = schema.createSchema();
}

//! @brief Sets the command implied by one or more command line options.
//! @param[in] command The numeric identifier of the command the user has
//! requested via command line arguments. Either a custom value or something
//! like StandardCommands::ShowHelp.
void ProgramArguments::setCommand(uint32_t command)
{
    _command = command;
}

//! @brief Processes the tokens parsed from the command line text.
//! @param[in] tokens The collection of pre-arsed tokens.
//! @param[out] error Receives a message detailing why processing filed.
//! @retval true The command line was successfully processed and validated.
//! @retval false The command line processing failed, error should detail why.
bool ProgramArguments::processArgumentTokens(const ArgumentCollection &tokens,
                                             String &error)
{
    // Reset the state of any variables with values left over from the last
    // set of arguments processed.
    clear();

    auto arg = tokens.begin();
    bool isOK = true;

    while (isOK && (arg != tokens.end()))
    {
        if (arg->ArgumentType == ArgumentToken::Argument)
        {
            isOK = processArgument(arg->Token, error);
            ++arg;
        }
        else
        {
            // It's an option.
            auto next = arg;
            ++next;
            size_t optionIndex = 0;
            bool hasOption = false;

            switch (arg->ArgumentType)
            {
            case ArgumentToken::ShortOption:
                hasOption = _schema.tryFindShortOption(*arg->Token.begin(), optionIndex);
                break;

            case ArgumentToken::LongOption:
                hasOption = _schema.tryFindLongOption(arg->Token, optionIndex);
                break;

            case ArgumentToken::Win32Option:
            default:
                if (arg->Token.getUtf32Length() > 1)
                {
                    hasOption = _schema.tryFindLongOption(arg->Token, optionIndex);
                }
                else
                {
                    hasOption = _schema.tryFindShortOption(*arg->Token.begin(), optionIndex);
                }
                break;
            }

            if (hasOption)
            {
                // Look up the definition of the option.
                const OptionDefinition &def = _schema.getOptionDefinition(optionIndex);

                if (def.getValueRequired() == OptionValue::None)
                {
                    // Process the option with no associated value.
                    isOK = processOption(def.getId(), arg->Original, String::Empty, error);
                    ++arg;
                }
                else
                {
                    // The option could be associated with a value.
                    if (arg->HasValue)
                    {
                        // Try processing with the explicitly associated value.
                        isOK = processOption(def.getId(), arg->Original, arg->Value, error);

                        ++arg;
                    }
                    else if ((next != tokens.end()) &&
                             (next->ArgumentType == ArgumentToken::Argument))
                    {
                        // The next token could be associated with the option.
                        isOK = processOption(def.getId(), arg->Original, next->Token, error);

                        if (isOK)
                        {
                            // Move past the option onto the associated value.
                            arg = next;

                            // Move past the value to the next option or argument.
                            ++arg;
                        }
                    }
                    else if (def.getValueRequired() == OptionValue::Optional)
                    {
                        isOK = processOption(def.getId(), arg->Original, String::Empty, error);
                        ++arg;
                    }
                    else
                    {
                        // An associated value was mandatory and none was available.
                        isOK = false;
                        error = String::format("Command line option '{0}' must "
                                               " be followed by an associated value.",
                                               { arg->Original });
                    }
                }
            }
            else
            {
                // The option was not found, create an error message.
                error = String::format("Unrecognised command line option '{0}'.",
                                       { arg->Original });
                isOK = false;
            }
        }
    }

    if (isOK)
    {
        // Perform final processing.
        postProcess();

        // Validate the results.
        isOK = validate(error);
    }

    return isOK;
}

}} // namespace Ag::Cli
////////////////////////////////////////////////////////////////////////////////

