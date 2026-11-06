//! @file ElfFileReader.cpp
//! @brief The definition of an object which can read symbols embedded within
//! a 32 or 64-bit ELF file.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <string>

#include <elf.h>
#include <cxxabi.h>

#include "CommandLine.hpp"
#include "ElfFileReader.hpp"
#include "SymbolDb.hpp"
#include "Utils.hpp"

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief Defines types for operating on a 32-bit ELF file.
struct Elf32_Traits
{
    using Ehdr = Elf32_Ehdr;
    using Phdr = Elf32_Phdr;
    using Shdr = Elf32_Shdr;
    using Sym = Elf32_Sym;

    using Half = Elf32_Half;
    using Word = Elf32_Word;
    using Sword = Elf32_Sword;
    using Xword = Elf32_Xword;
    using Sxword = Elf32_Sxword;
    using Addr = Elf32_Addr;
    using Off = Elf32_Off;
    using Section = Elf32_Section;
    using Versym = Elf32_Versym;

    static int getSymbolType(uint8_t st_info)
    {
        return ELF32_ST_TYPE(st_info);
    }
};

//! @brief Defines types for operating on a 64-bit ELF file.
struct Elf64_Traits
{
    using Ehdr = Elf64_Ehdr;
    using Phdr = Elf64_Phdr;
    using Shdr = Elf64_Shdr;
    using Sym = Elf64_Sym;

    using Half = Elf64_Half;
    using Word = Elf64_Word;
    using Sword = Elf64_Sword;
    using Xword = Elf64_Xword;
    using Sxword = Elf64_Sxword;
    using Addr = Elf64_Addr;
    using Off = Elf64_Off;
    using Section = Elf64_Section;
    using Versym = Elf64_Versym;

    static int getSymbolType(uint8_t st_info)
    {
        return ELF64_ST_TYPE(st_info);
    }
};

//! @brief A structure defining the initial fields of an ELF file which are
//! common between 32 and 64-bit files.
struct Elf_CommonHeader
{
    unsigned char   e_ident[EI_NIDENT];
    Elf32_Half      e_type;
    Elf32_Half      e_machine;
    Elf32_Word      e_version;
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Replaces all occurrences of one substring with another.
//! @param[in,out] target The string to replace text in.
//! @param[in] oldStr The substring to replace.
//! @param[in] newStr The substring to insert in place of oldStr.
void replaceAllOccurrances(std::string &target, const char *oldStr,
                           const char *newStr)
{
    size_t pos = target.find(oldStr);

    if (pos != std::string::npos)
    {
        std::string result;
        result.reserve(target.length() * 110 / 100);
        size_t oldStrLen = std::strlen(oldStr);
        size_t start = 0;

        while (pos != std::string::npos)
        {
            // Append text up to the recognised substring.
            result.append(target, start, pos - start);

            // Append the new text.
            result.append(newStr);

            // Prepare to find the next occurrence.
            start = pos + oldStrLen;
            pos = target.find(oldStr, start);
        }

        // Append the last of the unmodified text.
        result.append(target.c_str() + start,
                      target.size() - start);

        // Assign the return value.
        target = std::move(result);
    }
}

//! @brief De-mangles and fixes a function symbol read from an ELF symbol table.
//! @param[in] symbol A bounded array of symbol characters.
//! @return An STL string containing a display version of the symbol.
std::string fixupSymbol(const std::string_view &symbol)
{
    std::string fixed;

    // De-mangle the symbol.
    size_t length = 0;
    int status = 0;
    char *demangled = abi::__cxa_demangle(symbol.data(), nullptr, &length, &status);

    if ((demangled == nullptr) || (status != 0))
    {
        // Use the mangled symbol.
        fixed.assign(symbol);

        if ((fixed.empty() == false) && (fixed.back() != ')'))
        {
            // Add an empty parameter list.
            fixed.push_back('(');
            fixed.push_back(')');
        }
    }
    else
    {
        fixed.assign(demangled, length);
        free(demangled);
    }

    // Express anonymous namespaces in a consistent manner.
    replaceAllOccurrances(fixed, "(anonymous namespace)",
                          "<anon-namespace>");

    return fixed;
}

//! @brief Reads a string table from an ELF string table section.
//! @tparam Elf_Shdr The data type of the section header, specifying either
//! 32 or  64-bit format.
//! @param[in] fp The pointer to the open ELF binary file.
//! @param[in] sectionHeader A pointer to the string table section header.
//! @return The raw data read from the string table section.
template<typename Elf_Shdr>
std::vector<char> readElfStrings(FILE *fp, const Elf_Shdr *sectionHeader)
{
    // Verify the section is a string table and try to find it within the file.
    if ((sectionHeader->sh_type != SHT_STRTAB) ||
        (trySeek(fp, static_cast<int64_t>(sectionHeader->sh_offset)) == false))
    {
        return { };
    }

    // Prepare a block to receive the string data.
    std::vector<char> strings;
    size_t tableSize = static_cast<size_t>(sectionHeader->sh_size);
    strings.reserve(tableSize + 1);
    strings.resize(tableSize, '\0');

    // Read the string data as a single block.
    if (tryRead(fp, strings.data(), tableSize) == false)
    {
        strings.clear();
    }
    else
    {
        // Ensure the table is null terminated.
        strings.push_back('\0');
    }

    return strings;
}

//! @brief Reads symbols from an ELF binary file.
//! @tparam Elf The traits specifying various data types of the format, either
//! Elf32_Traits or Elf64_Traits.
//! @param[in] elfFile A pointer to the open ELF binary file positioned just after
//! reading the Elf_CommonHeader at the beginning of the file.
//! @param[in] commonHeader The format-agnostic data read from the beginning
//! of the file.
//! @param[out] symbols The database to receive the symbols read from the file.
//! @param[out] error A string to receive and error message if extraction fails.
template<typename Elf>
void readElfSymbols(FILE *elfFile, const Elf_CommonHeader &commonHeader,
                    SymbolDb &symbols, std::string &error)
{
    typename Elf::Ehdr header;
    memcpy(&header, &commonHeader, sizeof(commonHeader));

    // Read the rest of the header.
    if (tryRead(elfFile, offsetPtr<void>(&header, sizeof(commonHeader)),
                sizeof(header) - sizeof(commonHeader)) == false)
    {
        error.assign("Failed to read complete ELF header.");
        return;
    }
    else if (header.e_shstrndx == SHN_UNDEF)
    {
        error.assign("No section table was embedded in the ELF file.");
        return;
    }
    else if (trySeek(elfFile, header.e_shoff) == false)
    {
        error.assign("Failed to find ELF section table.");
        return;
    }

    // Read the section table.
    size_t sectionTableSize = header.e_shnum * header.e_shentsize;

    std::vector<uint8_t> sectionTableBuffer;
    sectionTableBuffer.resize(sectionTableSize, 0);

    if (tryRead(elfFile, sectionTableBuffer.data(), sectionTableSize) == false)
    {
        error.assign("Failed to read ELF section table.");
        return;
    }

    // Get the pointer to the section table entry describing
    // the string table holding the names of the sections.
    typename Elf::Shdr *sectionNameEntry =
        offsetPtr<typename Elf::Shdr>(sectionTableBuffer.data(),
                             header.e_shentsize * header.e_shstrndx);

    if ((sectionNameEntry->sh_type != SHT_STRTAB) ||
        (trySeek(elfFile, static_cast<int64_t>(sectionNameEntry->sh_offset)) == false))
    {
        error.assign("Failed to find ELF section name table.");
        return;
    }

    // Read the table defining the names of the sections.
    std::vector<char> sectionNameTable = readElfStrings(elfFile, sectionNameEntry);

    if (sectionNameTable.empty())
    {
        error.append("Failed to read ELF section name table.");
        return;
    }

    // Ensure the text is null-terminated.
    sectionNameTable.push_back('\0');

    // Read the table defining the names of the sections.
    typename Elf::Shdr *stringsEntry = nullptr;
    typename Elf::Shdr *symbolsEntry = nullptr;
    typename Elf::Addr baseOfCode = 0;

    for (uint16_t index = 0; index < header.e_shnum; ++index)
    {
        typename Elf::Shdr *entry = offsetPtr<typename Elf::Shdr>(sectionTableBuffer.data(),
                                                                  header.e_shentsize * index);

        const char *name = sectionNameTable.data() + entry->sh_name;

        if ((entry->sh_type == SHT_STRTAB) &&
            (strcmp(name, ".strtab") == 0))
        {
            stringsEntry = entry;
        }
        else if ((entry->sh_type == SHT_SYMTAB) &&
                 (strcmp(name, ".symtab") == 0))
        {
            symbolsEntry = entry;
        }
        else if ((entry->sh_type == SHT_PROGBITS) &&
                 (strcmp(name, ".text") == 0))
        {
            baseOfCode = entry->sh_addr - entry->sh_offset;
        }
    }

    if (stringsEntry == nullptr)
    {
        error.assign("Failed to find section containing ELF string table.");
        return;
    }
    else if (symbolsEntry == nullptr)
    {
        error.assign("Failed to find section containing ELF symbols.");
        return;
    }

    std::vector<char> stringTable = readElfStrings(elfFile, stringsEntry);

    if (stringTable.empty())
    {
        error.append("Failed to read ELF string table.");
        return;
    }

    int64_t symbolTableOffset = static_cast<int64_t>(symbolsEntry->sh_offset);
    size_t symbolTableSize = static_cast<size_t>(symbolsEntry->sh_size);
    size_t symbolSize = static_cast<size_t>(symbolsEntry->sh_entsize);
    size_t symbolCount = symbolTableSize / symbolSize;

    if (trySeek(elfFile, symbolTableOffset) == false)
    {
        error.assign("Failed to find ELF symbol table data.");
        return;
    }

    // Iterate through the symbol table, assigning string symbols and
    // de-mangling them were necessary.
    std::vector<uint8_t> symbolBuffer;

    symbolBuffer.resize(static_cast<size_t>(symbolsEntry->sh_entsize));
    const typename Elf::Sym *symbolEntry = reinterpret_cast<typename Elf::Sym *>(symbolBuffer.data());

    for (size_t i = 0; i < symbolCount; ++i)
    {
        if (tryRead(elfFile, symbolBuffer.data(), symbolSize) == false)
        {
            appendFormat(error, "Failed to read ELF symbol #%zi.", i);
            symbols.clear();

            return;
        }

        // Ensure the symbol has a name and points to something that
        // takes up sapce.
        if ((symbolEntry->st_name == 0) || (symbolEntry->st_size < 1))
            continue;

        // Ignore symbols which aren't functions.
        if (Elf::getSymbolType(symbolEntry->st_info) != STT_FUNC)
            continue;

        // It's a function symbol.
        //size_t fnStart = static_cast<size_t>(entry.Symbol.st_value) - baseOfCode;
        //size_t fnEnd = static_cast<size_t>(entry.Symbol.st_size) + fnStart;

        typename Elf::Addr fnOffset = symbolEntry->st_value - baseOfCode;

        // Ignore unhelpful symbols.
        std::string_view rawSymbolName(stringTable.data() + symbolEntry->st_name);
        std::string symbolName = fixupSymbol(rawSymbolName);

        // Add the symbol to the database.
        symbols.addSymbol(fnOffset, symbolName);
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ElfFileReader Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to extract the symbols from an ELF file, if any.
//! @param[in] args The arguments parsed from the command line.
ElfFileReader::ElfFileReader(const CommandLine &args) :
    _inputFile(args.getInputFile())
{
}

//! @brief Reads symbols from the file passed to the constructor into a database.
//! @param[in] symbols The database to fill with symbol definitions.
//! @param[in] error Receives details of an error if the process fails.
void ElfFileReader::readSymbols(SymbolDb &symbols, std::string &error)
{
    error.clear();

    StdFilePtr elfFile;
    error.clear();

    // Open the file for binary reading.
    if (tryOpenFile(_inputFile.c_str(), "rb", elfFile))
    {
        // Read and validate the initial ELF header.
        Elf_CommonHeader signatureHeader;

        if (tryRead(elfFile.get(), &signatureHeader, sizeof(signatureHeader)) == false)
        {
            error.assign("Failed to read initial ELF header.");
        }
        else if ((signatureHeader.e_ident[EI_MAG0] != ELFMAG0) ||
                 (signatureHeader.e_ident[EI_MAG1] != ELFMAG1) ||
                 (signatureHeader.e_ident[EI_MAG2] != ELFMAG2) ||
                 (signatureHeader.e_ident[EI_MAG3] != ELFMAG3))
        {
            error.assign("Invalid ELF file signature.");
        }
        else if ((signatureHeader.e_ident[EI_VERSION] != EV_CURRENT) ||
                 (signatureHeader.e_version != EV_CURRENT))
        {
            error.assign("Invalid ELF file version.");
        }
        else if ((signatureHeader.e_type != ET_EXEC) && (signatureHeader.e_type != ET_DYN))
        {
            error.assign("Invalid ELF file type.");
        }
        else if (signatureHeader.e_ident[EI_CLASS] == ELFCLASS32)
        {
            // Read symbols using 32-bit data structures.
            readElfSymbols<Elf32_Traits>(elfFile.get(), signatureHeader, symbols, error);
        }
        else if (signatureHeader.e_ident[EI_CLASS] == ELFCLASS64)
        {
            // Read symbols using 64-bit data structures.
            readElfSymbols<Elf64_Traits>(elfFile.get(), signatureHeader, symbols, error);
        }
        else
        {
            error.assign("Unknown ELF file class.");
        }
    }
    else
    {
        appendFormat(error, "Failed to open map file '%s'.",
                     _inputFile.c_str());
    }
}

#endif // ifndef _WIN32

////////////////////////////////////////////////////////////////////////////////

