//! @file GnuMapFileReader.hpp
//! @brief The declaration of an object which can read map files produced by the
//! GNU ld linker.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2023
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SYMBOL_PACKAGER_GNU_MAP_FILE_READER_HPP__
#define __AG_SYMBOL_PACKAGER_GNU_MAP_FILE_READER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class CommandLine;
class SymbolDb;

//! @brief An object which can read map files produced by the GNU ld linker.
class GnuMapFileReader
{
public:
    // Construction/Destruction
    GnuMapFileReader(const CommandLine &args);

    // Operations
    void readSymbols(SymbolDb &symbols, std::string &error);
private:
    // Internal Fields
    std::string _inputFile;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
