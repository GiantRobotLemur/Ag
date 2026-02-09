//! @file Ag/Core/ProgramArguments.hpp
//! @brief The declaration of an object which manages command line argument
//! parsing, processing and verification.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_PROGRAM_ARGUMENTS_HPP__
#define __AG_CORE_PROGRAM_ARGUMENTS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "CommandLineSchema.hpp"

namespace Ag {

namespace Cli {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class ArgumentCollection;

//! @brief An object used to process command line arguments and store
//! information relevant to the application.
class ProgramArguments
{
protected:
    // Construction/Destruction
    ProgramArguments();
public:
    ProgramArguments(const Schema &schema);
    virtual ~ProgramArguments() = default;

    // Accessors
    const String &getProgramFile() const;
    const Schema &getSchema() const;
    uint32_t getCommand() const;
    bool hasCommand() const;
    bool hasStandardCommand() const;

    // Operations
    bool tryParse(wchar_cptr_t win32CommandLine, String &error);
    bool tryParse(int argc, const char * const *argv, String &error);
    bool tryParse(int argc, const wchar_t * const *argv, String &error);

    virtual void showHelp() const;
    virtual void showVersion() const;

    // Overrides
    virtual bool tryProcessStandardCommand() const;
protected:
    virtual bool processOption(uint32_t id, const String &original,
                               const String &value, String &error);
    virtual bool processArgument(const String &argument, String &error);
    virtual bool validate(String &error) const;
    virtual void postProcess();
    virtual void clear();

    // Internal Functions
    void setSchema(const SchemaBuilder &schema);
    void setCommand(uint32_t command);
private:
    bool processArgumentTokens(const ArgumentCollection &tokens, String &error);

    // Internal Fields
    Schema _schema;
    String _programFile;
    uint32_t _command;
};

}} // namespace Ag::Cli

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
