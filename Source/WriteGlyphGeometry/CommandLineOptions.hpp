//! @file WriteGlyphGeometry/CommandLineOptions.hpp
//! @brief The declaration of an object which manages options specified on the
//! command line.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __WRITE_GLYPH_GEOMETRY_COMMAND_LINE_OPTIONS_HPP__
#define __WRITE_GLYPH_GEOMETRY_XXX_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <string_view>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Defines commands that the application can execute.
enum class Command
{
    None,
    ShowHelp,
    WriteGeometry,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
struct GlyphSpec
{
    std::wstring Name;
    wchar_t Character;

    GlyphSpec(std::wstring_view &name, wchar_t character);
};

using GlyphSpecCollection = std::vector<GlyphSpec>;

//! @brief An object which manages options specified on the command line.
class CommandLineOptions
{
public:
    // Construction/Destruction
    CommandLineOptions();
    ~CommandLineOptions() = default;

    // Accessors
    Command getCommand() const { return _command; }
    const std::wstring &getOutputSourceFile() const { return _outputSourceFile; }
    const std::wstring &getFontName() const { return _fontName; }
    const std::wstring &getGlyphsFile() const { return _glyphsFile; }
    const GlyphSpecCollection &getGlyphs() const { return _namedGlyphs; }


    // Operations
    void displayHelp();
    bool tryParse(int argc, wchar_t **argv, std::wstring &error);
    GlyphSpecCollection readGlyphsFile(std::wstring &error) const;
private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    std::wstring _programName;
    std::wstring _programPath;
    std::wstring _outputSourceFile;
    std::wstring _glyphsFile;
    std::wstring _fontName;
    GlyphSpecCollection _namedGlyphs;
    Command _command;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
