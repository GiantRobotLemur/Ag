//! @file WriteGlyphGeometry/GlyphWriter.hpp
//! @brief The declaration of an object which simplifies and outputs the outline
//! of a glyph as literal C++ data values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __WRITE_GLYPH_GEOMETRY_GLYPH_WRITER_HPP__
#define __WRITE_GLYPH_GEOMETRY_GLYPH_WRITER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which simplifies and outputs the outline of a glyph as
//! literal C++ data values.
class GlyphWriter
{
public:
    // Construction/Destruction
    GlyphWriter() = delete;
    GlyphWriter(GlyphWriter &&) = delete;
    GlyphWriter(const GlyphWriter &) = delete;
    GlyphWriter &operator=(GlyphWriter &&) = delete;
    GlyphWriter &operator=(const GlyphWriter &) = delete;
    GlyphWriter(const std::vector<uint8_t> &glyphData);

    // Operations
    void write(FILE *stream, const std::wstring &name,
               double accuracyThreshold, double scaleX, double scaleY) const;
private:
    // Internal Functions
    const TTPOLYGONHEADER *getFirstFigure() const;
    bool tryGetNextFigure(const TTPOLYGONHEADER *&figure) const;
    const TTPOLYCURVE *getFirstCurve(const TTPOLYGONHEADER *figure) const;
    bool tryGetNextCurve(const TTPOLYGONHEADER *figure,
                         const TTPOLYCURVE *&curve) const;

    // Internal Fields
    const std::vector<uint8_t> &_glyphSource;
    size_t _figureCount;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
