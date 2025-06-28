//! @file WriteGlyphGeometry/CommandLineOptions.cpp
//! @brief The definition of an object which manages options specified on the
//! command line.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "CommandLineOptions.hpp"
#include "Helpers.hpp"

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
bool tryGetOptionValue(int argi, int argc, wchar_t **argv, std::wstring &value)
{
    int valueIndex = argi + 1;
    bool hasValue = false;

    if (valueIndex < argc)
    {
        value = argv[valueIndex];
        hasValue = true;
    }
    else
    {
        value.clear();
    }

    return hasValue;
}

bool tryParseGlyphSpec(GlyphSpecCollection &specs, const std::wstring_view &token)
{
    auto pos = token.find(L':');

    if (pos >= token.length())
        return false;

    std::wstring_view name(token.substr(0, pos));
    std::wstring_view charSpec(token.substr(pos + 1));

    // Ensure the name associated with the glyph forms a valid C++ symbol.
    if (name.empty() || charSpec.empty())
        return false;

    if ((name.front() != L'_') && (std::iswalpha(name.front()) == 0))
        return false;

    for (size_t i = 1, j = name.length(); i < j; ++i)
    {
        wchar_t ch = name[i];

        if ((ch != L'_') && (iswalnum(ch) == 0))
            return false;
    }

    if (charSpec.length() == 1)
    {
        // The character is a literal.
        specs.emplace_back(name, charSpec.front());

        return true;
    }
    else
    {
        // The character is a hexadecimal encoding.
        for (wchar_t ch : charSpec)
        {
            if (iswxdigit(ch) == 0)
                return false;
        }

        auto characterCode = wcstoul(charSpec.data(), nullptr, 16);

        if ((characterCode == ULONG_MAX) && (errno == ERANGE))
            return false;

        if (characterCode > WCHAR_MAX)
            return false;

        specs.emplace_back(name, static_cast<wchar_t>(characterCode));
        return true;
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GlyphSpec Member Definitions
////////////////////////////////////////////////////////////////////////////////
GlyphSpec::GlyphSpec(std::wstring_view &name, wchar_t character) :
    Name(name),
    Character(character)
{
}

////////////////////////////////////////////////////////////////////////////////
// CommandLineOptions Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty set of command line options.
CommandLineOptions::CommandLineOptions() :
    _command(Command::None)
{
}

//! @brief Writes command line help to the standard output stream.
void CommandLineOptions::displayHelp()
{
    wprintf_s(L"%s - A tool to output font glyph geometry as literal C++ data.\n"
              L"Usage: %s [<options>] [<Glyph specs>]\n\n",
              _programName.c_str(), _programName.c_str());

    _putws(
        L"Options:\n"
        L"/? or --help       Shows this help text\n"
        L"-s/--source <file> Specifies the name of the source file to write.\n"
        L"-f/--font <font>   Specifies the name of the font to extracts glyphs from.\n"
        L"-g/--glyphs <file> Specifies the name of a file specifying the glyphs to extract.\n"
        L"Glyph specs: '<name>:<character>'\n"
        L"   Where <name>      A C++ compatible symbol.\n"
        L"         <character> A literal character or hex character code.\n");
}

//! @brief Processes the command line argument tokens.
//! @param[in] argc The count of tokens.
//! @param[in] argv The command line argument tokens, the first is assumed to
//! be the path to the current program.
//! @param[out] error Receives text describing an error if one occurred.
//! @retval true The command line was successfully interpreted and valid.
//! @retval false The command line arguments were invalid, error contains details
//! as to why.
bool CommandLineOptions::tryParse(int argc, wchar_t **argv, std::wstring &error)
{
    error.clear();
    _command = Command::None;
    _outputSourceFile.clear();
    _fontName.clear();
    _namedGlyphs.clear();

    if (argc > 0)
    {
        // The first argument should be the program binary name.
        std::wstring_view path(argv[0]);

        size_t pos = path.find_last_of(L"\\/");

        if (pos < path.length())
        {
            _programPath = path.substr(0, pos);
            _programName = path.substr(pos + 1);
        }
        else
        {
            _programName = path;
        }

        // Remove the extension, if there is one.
        pos = _programName.find(L'.');

        if (pos < _programName.length())
        {
            _programName.erase(_programName.begin() + pos, _programName.end());
        }
    }
    else
    {
        // The arguments are invalid if there isn't even a program name.
        return false;
    }

    static const std::wstring_view helpArg1(L"/?");
    static const std::wstring_view helpArg2(L"--help");
    static const std::wstring_view sourceFileArg1(L"-s");
    static const std::wstring_view sourceFileArg2(L"--source");
    static const std::wstring_view fontArg1(L"-f");
    static const std::wstring_view fontArg2(L"--font");
    static const std::wstring_view glyphsArg1(L"-g");
    static const std::wstring_view glyphsArg2(L"--glyphs");

    // Process the arguments sequentially.
    for (int argi = 1; argi < argc; ++argi)
    {
        std::wstring_view arg(argv[argi]);

        if ((arg == helpArg1) || (arg == helpArg2))
        {
            _command = Command::ShowHelp;
        }
        else if ((arg == sourceFileArg1) || (arg == sourceFileArg2))
        {
            if (tryGetOptionValue(argi, argc, argv, _outputSourceFile) == false)
            {
                error.assign(L"No source file name specified with option '");
                error.append(arg);
                error.append(L"'.");
                return false;
            }

            ++argi;
            _command = Command::WriteGeometry;
        }
        else if ((arg == fontArg1) || (arg == fontArg2))
        {
            if (tryGetOptionValue(argi, argc, argv, _fontName) == false)
            {
                error.assign(L"No font name specified with option '");
                error.append(arg);
                error.append(L"'.");
                return false;
            }

            ++argi;
            _command = Command::WriteGeometry;
        }
        else if ((arg == glyphsArg1) || (arg == glyphsArg2))
        {
            if (tryGetOptionValue(argi, argc, argv, _glyphsFile) == false)
            {
                error.assign(L"No glyph file specified with option '");
                error.append(arg);
                error.append(L"'.");
                return false;
            }

            ++argi;
            _command = Command::WriteGeometry;
        }
        else if (tryParseGlyphSpec(_namedGlyphs, arg))
        {
            _command = Command::WriteGeometry;
        }
        else
        {
            error.assign(L"Unknown command line argument '");
            error.append(arg);
            error.append(L"'.");
            return false;
        }
    }

    // Validate the combination of arguments returned.
    bool isOK = false;

    switch (_command)
    {
    case Command::None:
    default:
        _command = Command::ShowHelp;
        isOK = true;
        break;

    case Command::ShowHelp:
        isOK = true;
        break;

    case Command::WriteGeometry:
        if (_outputSourceFile.empty())
        {
            error.assign(L"No output source files specified.");
        }
        else if (_fontName.empty())
        {
            error.assign(L"No font specified.");
        }
        else if (_namedGlyphs.empty() && _glyphsFile.empty())
        {
            error.assign(L"No glyphs requested.");
        }
        else
        {
            isOK = true;
        }
        break;
    }

    return isOK;
}

enum class LineTokenState
{
    BeforeToken,
    InToken,
    AfterToken,
};

GlyphSpecCollection CommandLineOptions::readGlyphsFile(std::wstring &error) const
{
    // TODO: Read the glyph file line by line and parse one specification
    // per line using tryParseGlyphSpec()
    GlyphSpecCollection glyphs;
    error.clear();

    std::wstring filePath = toFullPath(_glyphsFile);
    FILE *inputStream = _wfsopen(filePath.c_str(), L"r", _SH_DENYNO);

    if (inputStream == nullptr)
    {
        auto errorCode = errno;
        error.assign(L"Error: Failed to open glyph specification file '");
        error.append(filePath);
        error.append(L"'");
        appendOptionalCRTErrorMessage(error, errorCode);
    }
    else
    {
        std::wstring buffer;
        buffer.reserve(32);

        wint_t ch = 0;
        int lineNo = 1;

        LineTokenState state = LineTokenState::BeforeToken;

        do
        {
            ch = getwc(inputStream);

            if ((ch == WEOF) || (ch == L'\n'))
            {
                if (buffer.empty() == false)
                {
                    if (tryParseGlyphSpec(glyphs, buffer) == false)
                    {
                        wchar_t digits[12];
                        swprintf_s(digits, L"(%d)", lineNo);
                        error.assign(filePath);
                        error.append(digits);
                        error.append(L": error: Invalid glyph specification.");
                        ch = WEOF;
                    }

                    buffer.clear();
                }

                lineNo++;
                state = LineTokenState::BeforeToken;
                continue;
            }

            bool isWhiteSpace = std::iswspace(ch);

            switch (state)
            {
            case LineTokenState::BeforeToken:
                if (!isWhiteSpace)
                {
                    buffer.clear();
                    buffer.push_back(ch);
                    state = LineTokenState::InToken;
                }
                break;

            case LineTokenState::InToken:
                if (isWhiteSpace)
                {
                    state = LineTokenState::AfterToken;
                }
                else
                {
                    buffer.push_back(ch);
                }
                break;

            case LineTokenState::AfterToken:
                if (!isWhiteSpace)
                {
                    wchar_t digits[12];
                    swprintf_s(digits, L"(%d)", lineNo);
                    error.assign(filePath);
                    error.append(digits);
                    error.append(L": error: Unexpected characters after glyph specification.");
                    ch = WEOF;
                }
                break;
            }
        } while (ch != WEOF);

        fclose(inputStream);
        inputStream = nullptr;
    }

    return glyphs;
}

////////////////////////////////////////////////////////////////////////////////
