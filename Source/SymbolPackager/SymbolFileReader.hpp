//! @file SymbolFileReader.hpp
//! @brief The declaration of an object which reads symbols pre-packaged in
//! a file.
//! @date 2021-2023
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SYMBOL_PACKAGER_SYMBOL_FILE_READER_HPP__
#define __AG_SYMBOL_PACKAGER_SYMBOL_FILE_READER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class CommandLine;
class SymbolDb;

//! @brief An object which reads symbols pre-packaged in a file.
class SymbolFileReader
{
public:
    // Construction/Destruction
    SymbolFileReader(const CommandLine &args);

    // Accessors

    // Operations
    void readSymbols(SymbolDb &symbols, std::string &error);
private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    std::string _inputFile;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
