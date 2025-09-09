//! @file SymbolPackager/SymbolDb.hpp
//! @brief The declaration of an object which can store symbolic information to
//! be packaged as a file.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SYMBOL_PACKAGER_SYMBOL_DB_HPP__
#define __AG_SYMBOL_PACKAGER_SYMBOL_DB_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "Utils.hpp"

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
struct SymbolEntry
{
    uint64_t Offset;
    size_t SymbolId;
    std::string Symbol;

    SymbolEntry(uint64_t offset, const std::string &symbol);
    SymbolEntry(uint64_t offset, const BoundedString &symbol);
};

//! @brief An object which can store symbolic information to be packaged as a file.
class SymbolDb
{
public:
    // Construction/Destruction
    SymbolDb();

    // Operations
    void clear();
    void compile();
    void addSymbol(const SymbolEntry &symbol);
    void addSymbol(uint64_t offset, const std::string &symbol);
    void addSymbol(uint64_t offset, const BoundedString &symbol);
    bool writeSymbolFile(Ag::IStream *outputStream, bool compress) const;
    bool writeText(FILE *outputStream) const;
private:
    // Internal Functions
    bool writeSymbolData(Ag::IStream *outputStream) const;
    void reset();

    // Internal Fields
    std::vector<SymbolEntry> _symbolTable;
    std::vector<SymbolEntry *> _symbolIndex;
    uint32_t _maxSymbolLength;
    uint32_t _offsetDeltaBits;
    uint32_t _prefixBits;
    uint32_t _suffixBits;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
