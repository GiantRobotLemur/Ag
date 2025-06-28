//! @file WriteGlyphGeometry/Main.cpp
//! @brief The definition of the entry point to a tool which extracts glyph
//! geometry from fonts using Windows GDI.
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
#include "GlyphExtractor.hpp"
#include "GlyphWriter.hpp"
#include "Helpers.hpp"

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
FILE *createSourceFile(const std::wstring &fileName)
{
    std::wstring sourcePath = toFullPath(fileName);
    FILE *sourceStream = _wfsopen(sourcePath.c_str(), L"w", _SH_DENYNO);

    if (sourceStream == nullptr)
    {
        // Report error.
        auto fileError = errno;
        wprintf_s(L"Error: Failed to create file '%s'\n", sourcePath.c_str());

        std::wstring message = getCRTErrorMessage(fileError);
        if (message.empty())
        {
            putwchar(L'.');
            putwchar(L'\n');
        }
        else
        {
            wprintf_s(L": %s\n", message.c_str());
        }

        return nullptr;
    }

    auto name = getFileName(sourcePath);

    fwprintf_s(sourceStream, L"// %s\n", name.data());
    fputws(L"// Defines glyph contour data as polygons.\n", sourceStream);

    // Time-stamps on generated data messes with diffs.
    //__time64_t timeStamp;
    //tm timeDetail;
    //_time64(&timeStamp);
    //_localtime64_s(&timeDetail, &timeStamp);

    //fwprintf_s(sourceStream, L"// Generated on %.4d-%.2d-%.2d %.2d:%.2d:%.2d\n\n",
    //           timeDetail.tm_year + 1900, timeDetail.tm_mon, timeDetail.tm_mday,
    //           timeDetail.tm_hour, timeDetail.tm_min, timeDetail.tm_sec);

    fputws(L"#include <cstdint>\n", sourceStream);
    fputws(L"#include <utility>\n\n", sourceStream);

    return sourceStream;
}

int doExtractFontDefinitions(const CommandLineOptions &options)
{
    if (::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2) == false)
    {
        std::wstring errorMessage = getWin32ErrorMessage(::GetLastError());

        wprintf_s(L"Failed to set process DPI awareness: %s\n",
                  errorMessage.c_str());
        return 1;
    }

    GlyphExtractor extractor;
    std::wstring error;

    if (extractor.tryInitialise(options.getFontName(), error) == false)
    {
        _putws(error.c_str());
        return 1;
    }

    // Get the name of the source file to write.
    std::vector<uint8_t> geometryData;
    GLYPHMETRICS metrics;
    FILE *sourceStream = nullptr;
    int processResult = 0;

    GlyphSpecCollection glyphs;

    if (options.getGlyphsFile().empty() == false)
    {
        glyphs = options.readGlyphsFile(error);

        if (error.empty() == false)
        {
            _putws(error.c_str());
            return 1;
        }
    }

    const auto &inlineGlyphs = options.getGlyphs();
    std::copy(inlineGlyphs.begin(), inlineGlyphs.end(),
              std::back_inserter(glyphs));

    for (const auto &charSpec : glyphs)
    {
        if (extractor.tryExtractGlyphGeometry(charSpec.Character,
                                              metrics, geometryData,
                                              error) == false)
        {
            wprintf_s(L"Error: %s\n", error.c_str());
            processResult = 1;
            break;
        }

        if (sourceStream == nullptr)
        {
            // Lazily create the source file.
            sourceStream = createSourceFile(options.getOutputSourceFile());

            if (sourceStream == nullptr)
            {
                processResult = 1;
                break;
            }
        }

        // Create an object to simplify and write the geometry.
        GlyphWriter writer(geometryData);

        writer.write(sourceStream, charSpec.Name, 1.5, 1.0, 1.0);
    }

    if (sourceStream != nullptr)
    {
        // Close the source file, whether we were successful or not.
        fclose(sourceStream);
        sourceStream = nullptr;
    }

    return processResult;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
int wmain(int argc, wchar_t *argv[])
{
    int processResult = 1;

    CommandLineOptions programOptions;
    std::wstring error;

    if (programOptions.tryParse(argc, argv, error))
    {
        switch (programOptions.getCommand())
        {
        case Command::None:
        case Command::ShowHelp:
        default:
            programOptions.displayHelp();
            processResult = 0;
            break;

        case Command::WriteGeometry:
            processResult = doExtractFontDefinitions(programOptions);
            break;
        }
    }
    else
    {
        wprintf_s(L"Command line error: %s\n", error.c_str());
    }

    return processResult;
}

////////////////////////////////////////////////////////////////////////////////

