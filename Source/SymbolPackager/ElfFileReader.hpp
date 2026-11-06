//! @file ElfFileReader.hpp
//! @brief The declaration of an object which can read symbols embedded within
//! a 32 or 64-bit ELF file.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_SYMBOL_PACKAGER_ELF_FILE_READER_HPP_
#define HEADER_AG_SYMBOL_PACKAGER_ELF_FILE_READER_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class CommandLine;
class SymbolDb;

//! @brief An object which can read symbols embedded within a 32 or 64-bit
//! ELF file.
class ElfFileReader
{
public:
    // Construction/Destruction
    ElfFileReader(const CommandLine &args);

    // Operations
    void readSymbols(SymbolDb &symbols, std::string &error);
private:
    // Internal Fields
    std::string _inputFile;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
