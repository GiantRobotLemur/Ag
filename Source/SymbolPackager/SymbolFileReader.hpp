//! @file SymbolPackager/SymbolFileReader.hpp
//! @brief The declaration of an object which reads symbols pre-packaged in
//! a file.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
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

namespace Ag {
class IStream;
struct SymbolHeaderV1;
} // namespace Ag

//! @brief An object which reads symbols pre-packaged in a file.
class SymbolFileReader
{
public:
    // Construction/Destruction
    SymbolFileReader(const CommandLine &args);

    // Operations
    void readSymbols(SymbolDb &symbols, std::string &error);
private:
    // Internal Functions
    void readSymbolData(Ag::IStream *input, const Ag::SymbolHeaderV1 &header,
                        SymbolDb &symbols, std::string &error);

    // Internal Fields
    std::string _inputFile;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
