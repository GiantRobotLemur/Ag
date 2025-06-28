//! @file WriteGlyphGeometry/GlyphExtractor.hpp
//! @brief The declaration of an object which extracts the definition of glyphs
//! from a font.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __WRITE_GLYPH_GEOMETRY_GLYPH_EXTRACTOR_HPP__
#define __WRITE_GLYPH_GEOMETRY_GLYPH_EXTRACTOR_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which extracts the definition of glyphs from a font.
class GlyphExtractor
{
public:
    // Construction/Destruction
    GlyphExtractor();
    ~GlyphExtractor();

    // Operations
    void destroy();
    bool tryInitialise(const std::wstring_view &fontName,
                       std::wstring &error);
    bool tryExtractGlyphGeometry(wchar_t ch, GLYPHMETRICS &metrics,
                                 std::vector<uint8_t> &glyphData,
                                 std::wstring &error) const;
private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    HWND _desktopWindow;
    HDC _deviceContext;
    HFONT _fontResource;
    std::vector<uint8_t> _outlineTextMetricsData;
    LPOUTLINETEXTMETRICW _outlineTextMetrics;
    std::wstring_view _faceName;
    std::wstring_view _styleName;
    std::wstring_view _fullFontName;
    double _nativeSizeInPts;
    int _fontDpi;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
