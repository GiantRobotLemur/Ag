//! @file WriteGlyphGeometry/GlyphExtractor.cpp
//! @brief The definition of an object which extracts the definition of glyphs
//! from a font.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "GlyphExtractor.hpp"
#include "CommandLineOptions.hpp"
#include "Helpers.hpp"

////////////////////////////////////////////////////////////////////////////////
// GlyphExtractor Member Definitions
////////////////////////////////////////////////////////////////////////////////
GlyphExtractor::GlyphExtractor() :
    _desktopWindow(::GetDesktopWindow()),
    _deviceContext(nullptr),
    _fontResource(nullptr),
    _outlineTextMetrics(nullptr),
    _nativeSizeInPts(0.0),
    _fontDpi(96)
{
}

GlyphExtractor::~GlyphExtractor()
{
    destroy();
}

void GlyphExtractor::destroy()
{
    if (_fontResource != nullptr)
    {
        ::DeleteObject(_fontResource);
        _fontResource = nullptr;
    }

    if (_deviceContext != nullptr)
    {
        ::ReleaseDC(_desktopWindow, _deviceContext);
        _deviceContext = nullptr;
    }

    _outlineTextMetrics = nullptr;
    _outlineTextMetricsData.clear();
}

//! @brief Attempts to initialise the object with a font to extract glyphs from.
//! @param[in] fontName The name of the font to select.
//! @param[out] error Receives an error message if initialisation fails.
//! @retval true Initialisation was successful.
//! @retval false Initialisation failed, error is updated to describe why.
bool GlyphExtractor::tryInitialise(const std::wstring_view &fontName,
                                   std::wstring &error)
{
    destroy();

    if (fontName.length() >= (LF_FACESIZE - 1))
    {
        error.assign(L"Font name '");
        error.append(fontName);
        error.append(L"' too long.");
        return false;
    }

    // Reset the thread error state.
    ::SetLastError(ERROR_SUCCESS);

    _deviceContext = ::GetDC(_desktopWindow);

    if (_deviceContext == nullptr)
    {
        uint32_t errorCode = ::GetLastError();
        error.assign(L"Failed to obtain a device context for the desktop window");
        appendOptionalErrorMessage(error, errorCode);

        return false;
    }

    // Note the DPI scale used in conversions for later.
    _fontDpi = ::GetDeviceCaps(_deviceContext, LOGPIXELSY);

    LOGFONTW fontInfo;
    ZeroMemory(&fontInfo, sizeof(fontInfo));
    wcsncpy_s(fontInfo.lfFaceName, fontName.data(), fontName.size());

    HFONT probeFont = ::CreateFontIndirectW(&fontInfo);

    if (probeFont == nullptr)
    {
        uint32_t errorCode = ::GetLastError();

        error.assign(L"Failed to create initial font '");
        error.append(fontName);
        error.append(L"'");
        appendOptionalErrorMessage(error, errorCode);

        return false;
    }

    // Get a copy of the information about the font.
    if (::GetObjectW(probeFont, sizeof(fontInfo), &fontInfo) != sizeof(fontInfo))
    {
        uint32_t errorCode = ::GetLastError();

        error.assign(L"Failed to query font information for '");
        error.append(fontName);
        error.append(L"'");
        appendOptionalErrorMessage(error, errorCode);
        ::DeleteObject(probeFont);

        return false;
    }

    // Select the font for use.
    HGDIOBJ oldFont = ::SelectObject(_deviceContext, reinterpret_cast<HGDIOBJ>(probeFont));

    uint32_t requiredSize = ::GetOutlineTextMetricsW(_deviceContext, 0, nullptr);
    bool isOK = false;

    if (requiredSize > 0)
    {
        _outlineTextMetricsData.resize(requiredSize);
        _outlineTextMetrics = reinterpret_cast<LPOUTLINETEXTMETRICW>(_outlineTextMetricsData.data());

        ::GetOutlineTextMetricsW(_deviceContext, requiredSize, _outlineTextMetrics);

        if ((_outlineTextMetrics->otmTextMetrics.tmPitchAndFamily & TMPF_VECTOR) == 0)
        {
            error.assign(L"'");
            error.append(fontName);
            error.append(L"' it not a vector font.");
        }
        else
        {
            _faceName = std::wstring_view(reinterpret_cast<LPWSTR>(_outlineTextMetricsData.data() + reinterpret_cast<uintptr_t>(_outlineTextMetrics->otmpFaceName)));
            _styleName = std::wstring_view(reinterpret_cast<LPWSTR>(_outlineTextMetricsData.data() + reinterpret_cast<uintptr_t>(_outlineTextMetrics->otmpStyleName)));
            _fullFontName = std::wstring_view(reinterpret_cast<LPWSTR>(_outlineTextMetricsData.data() + reinterpret_cast<uintptr_t>(_outlineTextMetrics->otmpFullName)));

            fontInfo.lfHeight = -static_cast<LONG>(_outlineTextMetrics->otmEMSquare);

            // Calculate the size of the ideal font in points (72ths of an inch).
            _nativeSizeInPts = (_outlineTextMetrics->otmEMSquare * 72.0) / _fontDpi;

            _fontResource = ::CreateFontIndirectW(&fontInfo);

            if (_fontResource == nullptr)
            {
                uint32_t errorCode = ::GetLastError();

                error.assign(L"Failed to create native font '");
                error.append(fontName);
                error.append(L"'");
                appendOptionalErrorMessage(error, errorCode);
            }
            else
            {
                isOK = true;
            }
        }
    }
    else
    {
        uint32_t errorCode = ::GetLastError();
        error.assign(L"Failed to query outline text metrics for font '");
        error.append(fontName);
        error.append(L"'");
        appendOptionalErrorMessage(error, errorCode);
    }

    // Restore the old font.
    ::SelectObject(_deviceContext, oldFont);
    ::DeleteObject(probeFont);

    return isOK;
}

bool GlyphExtractor::tryExtractGlyphGeometry(wchar_t ch, GLYPHMETRICS &metrics,
                                             std::vector<uint8_t> &glyphData,
                                             std::wstring &error) const
{
    glyphData.clear();
    error.clear();
    ZeroMemory(&metrics, sizeof(metrics));

    if ((_deviceContext == nullptr) || (_fontResource == nullptr))
    {
        error.assign(L"Glyph extraction not initialised.");
        return false;
    }

    HFONT oldFont = SelectFont(_deviceContext, _fontResource);
    WORD glyphIndex = 0xFFFF;

    // Translate the character into a glyph index.
    ::SetLastError(ERROR_SUCCESS);

    uint32_t glyphCount = ::GetGlyphIndicesW(_deviceContext, &ch, 1,
                                             &glyphIndex,
                                             GGI_MARK_NONEXISTING_GLYPHS);

    if ((glyphCount == GDI_ERROR) || (glyphIndex == 0xFFFF))
    {
        uint32_t errorCode = ::GetLastError();
        SelectFont(_deviceContext, oldFont);

        error.assign(L"Failed to find glyph to match character '%c'", ch);
        appendOptionalErrorMessage(error, errorCode);
        return false;
    }

    MAT2 transform = { 0 };
    transform.eM11.value = 1;
    transform.eM22.value = 1;

    uint32_t size = ::GetGlyphOutlineW(_deviceContext, glyphIndex,
                                       GGO_NATIVE | GGO_GLYPH_INDEX,
                                       &metrics, 0, nullptr, &transform);

    bool isOK = false;

    if ((size != GDI_ERROR) && (size > 0))
    {
        glyphData.resize(size, 0);

        size = ::GetGlyphOutlineW(_deviceContext, glyphIndex,
                                  GGO_NATIVE | GGO_GLYPH_INDEX,
                                  &metrics, size, glyphData.data(),
                                  &transform);
    }

    if ((size == GDI_ERROR) || (size == 0))
    {
        uint32_t errorCode = ::GetLastError();
        SelectFont(_deviceContext, oldFont);

        error.assign(L"Failed to query glyph geometry for character '%c'", ch);
        appendOptionalErrorMessage(error, errorCode);
    }
    else
    {
        isOK = true;
    }

    SelectFont(_deviceContext, oldFont);

    return isOK;
}

////////////////////////////////////////////////////////////////////////////////

