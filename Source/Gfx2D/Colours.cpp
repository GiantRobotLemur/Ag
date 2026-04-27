//! @file Gfx2D/Colours.cpp
//! @brief The definition of a static set of named colours.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <utility>
#include <string_view>
#include <unordered_map>

#include "Ag/Core/Exception.hpp"

#include "Ag/Gfx2D/Colour.hpp"
#include "Ag/Gfx2D/Colours.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {
namespace Colours {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
using SourceColour = std::pair<utf8_cptr_t, uint32_t>;

struct NamedColour
{
    Colour Value;
    String Key;
    String DisplayName;
    uint32_t RawColour;
};

using ColourAliasMap = std::unordered_map<String, Index>;
using RawColourMap = StaticMap<uint32_t, Index>;

Colour colourFromBGRA(uint32_t bgra) noexcept
{
    return Colour(static_cast<float>((bgra >> 16) & 0xFF) / 255.0f,
                  static_cast<float>((bgra >> 8) & 0xFF) / 255.0f,
                  static_cast<float>(bgra & 0xFF) / 255.0f,
                  static_cast<float>((bgra >> 24) & 0xFF) / 255.0f);
}

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
// Colour definitions from https://www.w3schools.com/colors/colors_groups.asp
static const SourceColour __sourceColours[] =
{
    // Pink Colours
    { "Pink",                   0xFFFFC0CB },
    { "LightPink",              0xFFFFB6C1 },
    { "HotPink",                0xFFFF69B4 },
    { "DeepPink",               0xFFFF1493 },
    { "PaleVioletRed",          0xFFDB7093 },
    { "MediumVioletRed",        0xFFC71585 },

    // Purple Colours
    { "Lavender",               0xFFE6E6FA },
    { "Thistle",                0xFFD8BFD8 },
    { "Plum",                   0xFFDDA0DD },
    { "Orchid",                 0xFFDA70D6 },
    { "Violet",                 0xFFEE82EE },
    { "Fuchsia",                0xFFFF00FF },
    { "Magenta",                0xFFFF00FF },
    { "MediumOrchid",           0xFFBA55D3 },
    { "DarkOrchid",             0xFF9932CC },
    { "DarkViolet",             0xFF9400D3 },
    { "BlueViolet",             0xFF8A2BE2 },
    { "DarkMagenta",            0xFF8B008B },
    { "Purple",                 0xFF800080 },
    { "MediumPurple",           0xFF9370DB },
    { "MediumSlateBlue",        0xFF7B68EE },
    { "SlateBlue",              0xFF6A5ACD },
    { "DarkSlateBlue",          0xFF483D8B },
    { "RebeccaPurple",          0xFF663399 },
    { "Indigo",                 0xFF4B0082 },

    // Red Colours
    { "LightSalmon",            0xFFFFA07A },
    { "Salmon",                 0xFFFA8072 },
    { "DarkSalmon",             0xFFE9967A },
    { "LightCoral",             0xFFF08080 },
    { "IndianRed",              0xFFCD5C5C },
    { "Crimson",                0xFFDC143C },
    { "Red",                    0xFFFF0000 },
    { "FireBrick",              0xFFB22222 },
    { "DarkRed",                0xFF8B0000 },

    // Orange Colours
    { "Orange",                 0xFFFFA500 },
    { "DarkOrange",             0xFFFF8C00 },
    { "Coral",                  0xFFFF7F50 },
    { "Tomato",                 0xFFFF6347 },
    { "OrangeRed",              0xFFFF4500 },

    // Yellow Colours
    { "Gold",                   0xFFFFD700 },
    { "Yellow",                 0xFFFFFF00 },
    { "LightYellow",            0xFFFFFFE0 },
    { "LemonChiffon",           0xFFFFFACD },
    { "LightGoldenRodYellow",   0xFFFAFAD2 },
    { "PapayaWhip",             0xFFFFEFD5 },
    { "Moccasin",               0xFFFFE4B5 },
    { "PeachPuff",              0xFFFFDAB9 },
    { "PaleGoldenRod",          0xFFEEE8AA },
    { "Khaki",                  0xFFF0E68C },
    { "DarkKhaki",              0xFFBDB76B },

    // Green Colours
    { "GreenYellow",            0xFFADFF2F },
    { "Chartreuse",             0xFF7FFF00 },
    { "LawnGreen",              0xFF7CFC00 },
    { "Lime",                   0xFF00FF00 },
    { "LimeGreen",              0xFF32CD32 },
    { "PaleGreen",              0xFF98FB98 },
    { "LightGreen",             0xFF90EE90 },
    { "MediumSpringGreen",      0xFF00FA9A },
    { "SpringGreen",            0xFF00FF7F },
    { "MediumSeaGreen",         0xFF3CB371 },
    { "SeaGreen",               0xFF2E8B57 },
    { "ForestGreen",            0xFF228B22 },
    { "Green",                  0xFF008000 },
    { "DarkGreen",              0xFF006400 },
    { "YellowGreen",            0xFF9ACD32 },
    { "OliveDrab",              0xFF6B8E23 },
    { "DarkOliveGreen",         0xFF556B2F },
    { "MediumAquaMarine",       0xFF66CDAA },
    { "DarkSeaGreen",           0xFF8FBC8F },
    { "LightSeaGreen",          0xFF20B2AA },
    { "DarkCyan",               0xFF008B8B },
    { "Teal",                   0xFF008080 },

    // Cyan Colours
    { "Aqua",                   0xFF00FFFF },
    { "Cyan",                   0xFF00FFFF },
    { "LightCyan",              0xFFE0FFFF },
    { "PaleTurquoise",          0xFFAFEEEE },
    { "Aquamarine",             0xFF7FFFD4 },
    { "Turquoise",              0xFF40E0D0 },
    { "MediumTurquoise",        0xFF48D1CC },
    { "DarkTurquoise",          0xFF00CED1 },

    // Blue Colours
    { "CadetBlue",              0xFF5F9EA0 },
    { "SteelBlue",              0xFF4682B4 },
    { "LightSteelBlue",         0xFFB0C4DE },
    { "LightBlue",              0xFFADD8E6 },
    { "PowderBlue",             0xFFB0E0E6 },
    { "LightSkyBlue",           0xFF87CEFA },
    { "SkyBlue",                0xFF87CEEB },
    { "CornflowerBlue",         0xFF6495ED },
    { "DeepSkyBlue",            0xFF00BFFF },
    { "DodgerBlue",             0xFF1E90FF },
    { "RoyalBlue",              0xFF4169E1 },
    { "Blue",                   0xFF0000FF },
    { "MediumBlue",             0xFF0000CD },
    { "DarkBlue",               0xFF00008B },
    { "Navy",                   0xFF000080 },
    { "MidnightBlue",           0xFF191970 },

    // Brown Colours
    { "Cornsilk",               0xFFFFF8DC },
    { "BlanchedAlmond",         0xFFFFEBCD },
    { "Bisque",                 0xFFFFE4C4 },
    { "NavajoWhite",            0xFFFFDEAD },
    { "Wheat",                  0xFFF5DEB3 },
    { "BurlyWood",              0xFFDEB887 },
    { "Tan",                    0xFFD2B48C },
    { "RosyBrown",              0xFFBC8F8F },
    { "SandyBrown",             0xFFF4A460 },
    { "GoldenRod",              0xFFDAA520 },
    { "DarkGoldenRod",          0xFFB8860B },
    { "Peru",                   0xFFCD853F },
    { "Chocolate",              0xFFD2691E },
    { "Olive",                  0xFF808000 },
    { "SaddleBrown",            0xFF8B4513 },
    { "Sienna",                 0xFFA0522D },
    { "Brown",                  0xFFA52A2A },
    { "Maroon",                 0xFF800000 },

    // White Colours
    { "White",                  0xFFFFFFFF },
    { "Snow",                   0xFFFFFAFA },
    { "HoneyDew",               0xFFF0FFF0 },
    { "MintCream",              0xFFF5FFFA },
    { "Azure",                  0xFFF0FFFF },
    { "AliceBlue",              0xFFF0F8FF },
    { "GhostWhite",             0xFFF8F8FF },
    { "WhiteSmoke",             0xFFF5F5F5 },
    { "SeaShell",               0xFFFFF5EE },
    { "Beige",                  0xFFF5F5DC },
    { "OldLace",                0xFFFDF5E6 },
    { "FloralWhite",            0xFFFFFAF0 },
    { "Ivory",                  0xFFFFFFF0 },
    { "AntiqueWhite",           0xFFFAEBD7 },
    { "Linen",                  0xFFFAF0E6 },
    { "LavenderBlush",          0xFFFFF0F5 },
    { "MistyRose",              0xFFFFE4E1 },

    // Grey Colours
    { "Gainsboro",              0xFFDCDCDC },
    { "LightGray",              0xFFD3D3D3 },
    { "Silver",                 0xFFC0C0C0 },
    { "DarkGray",               0xFFA9A9A9 },
    { "DimGray",                0xFF696969 },
    { "Gray",                   0xFF808080 },
    { "LightSlateGray",         0xFF778899 },
    { "SlateGray",              0xFF708090 },
    { "DarkSlateGray",          0xFF2F4F4F },
    { "Black",                  0xFF000000 },

    // Misc
    { "Transparent",            0x00000000 },
};

ColourAliasMap __colourIndexByNameKey;
RawColourMap::MappingType __rawColourMappings[std::size(__sourceColours)];
RawColourMap __colourIndexByRawColour;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the internal table of named colours, populating and indexing
//! them on first call.
const NamedColour *getNamedColours()
{
    static NamedColour namedColours[std::size(__sourceColours)];
    static bool isInitialised = false;

    static_assert(std::size(__sourceColours) <= std::numeric_limits<Index>::max(),
                  "The index data type doesn't have enough range.");

    if (isInitialised == false)
    {
        // Ensure we only do this once.
        isInitialised = true;

        // Ensure the array is initialised and the contents indexed.
        Index index = 0;
        float components[4];

        for (const auto &source : __sourceColours)
        {
            auto &namedColour = namedColours[index];
            components[0] = ((source.second >> 16) & 0xFF) / 255.0f;
            components[1] = ((source.second >> 8) & 0xFF) / 255.0f;
            components[2] = (source.second & 0xFF) / 255.0f;
            components[3] = ((source.second >> 24) & 0xFF) / 255.0f;

            namedColour.RawColour = source.second;
            namedColour.DisplayName = source.first;
            namedColour.Key = namedColour.DisplayName.toUpper();
            namedColour.Value = Colour(components);

            // Index the colour by name and raw RGBA value.
            __colourIndexByNameKey[namedColour.Key] = index;
            __rawColourMappings[index].first = source.second;
            __rawColourMappings[index].second = index;

            ++index;
        }

        __colourIndexByRawColour = RawColourMap(__rawColourMappings);
    }

    return namedColours;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Global Data Definitions
////////////////////////////////////////////////////////////////////////////////
// Pink Colours
const Colour Pink = colourFromBGRA(__sourceColours[0].second);
const Colour LightPink = colourFromBGRA(__sourceColours[1].second);
const Colour HotPink = colourFromBGRA(__sourceColours[2].second);
const Colour DeepPink = colourFromBGRA(__sourceColours[3].second);
const Colour PaleVioletRed = colourFromBGRA(__sourceColours[4].second);
const Colour MediumVioletRed = colourFromBGRA(__sourceColours[5].second);

// Purple Colours
const Colour Lavender = colourFromBGRA(__sourceColours[6].second);
const Colour Thistle = colourFromBGRA(__sourceColours[7].second);
const Colour Plum = colourFromBGRA(__sourceColours[8].second);
const Colour Orchid = colourFromBGRA(__sourceColours[9].second);
const Colour Violet = colourFromBGRA(__sourceColours[10].second);
const Colour Fuchsia = colourFromBGRA(__sourceColours[11].second);
const Colour Magenta = colourFromBGRA(__sourceColours[12].second);
const Colour MediumOrchid = colourFromBGRA(__sourceColours[13].second);
const Colour DarkOrchid = colourFromBGRA(__sourceColours[14].second);
const Colour DarkViolet = colourFromBGRA(__sourceColours[15].second);
const Colour BlueViolet = colourFromBGRA(__sourceColours[16].second);
const Colour DarkMagenta = colourFromBGRA(__sourceColours[17].second);
const Colour Purple = colourFromBGRA(__sourceColours[18].second);
const Colour MediumPurple = colourFromBGRA(__sourceColours[19].second);
const Colour MediumSlateBlue = colourFromBGRA(__sourceColours[20].second);
const Colour SlateBlue = colourFromBGRA(__sourceColours[21].second);
const Colour DarkSlateBlue = colourFromBGRA(__sourceColours[22].second);
const Colour RebeccaPurple = colourFromBGRA(__sourceColours[23].second);
const Colour Indigo = colourFromBGRA(__sourceColours[24].second);

// Red Colours
const Colour LightSalmon = colourFromBGRA(__sourceColours[25].second);
const Colour Salmon = colourFromBGRA(__sourceColours[26].second);
const Colour DarkSalmon = colourFromBGRA(__sourceColours[27].second);
const Colour LightCoral = colourFromBGRA(__sourceColours[28].second);
const Colour IndianRed = colourFromBGRA(__sourceColours[29].second);
const Colour Crimson = colourFromBGRA(__sourceColours[30].second);
const Colour Red = colourFromBGRA(__sourceColours[31].second);
const Colour FireBrick = colourFromBGRA(__sourceColours[32].second);
const Colour DarkRed = colourFromBGRA(__sourceColours[33].second);

// Orange Colours
const Colour Orange = colourFromBGRA(__sourceColours[34].second);
const Colour DarkOrange = colourFromBGRA(__sourceColours[35].second);
const Colour Coral = colourFromBGRA(__sourceColours[36].second);
const Colour Tomato = colourFromBGRA(__sourceColours[37].second);
const Colour OrangeRed = colourFromBGRA(__sourceColours[38].second);

// Yellow Colours
const Colour Gold = colourFromBGRA(__sourceColours[39].second);
const Colour Yellow = colourFromBGRA(__sourceColours[40].second);
const Colour LightYellow = colourFromBGRA(__sourceColours[41].second);
const Colour LemonChiffon = colourFromBGRA(__sourceColours[42].second);
const Colour LightGoldenRodYellow = colourFromBGRA(__sourceColours[43].second);
const Colour PapayaWhip = colourFromBGRA(__sourceColours[44].second);
const Colour Moccasin = colourFromBGRA(__sourceColours[45].second);
const Colour PeachPuff = colourFromBGRA(__sourceColours[46].second);
const Colour PaleGoldenRod = colourFromBGRA(__sourceColours[47].second);
const Colour Khaki = colourFromBGRA(__sourceColours[48].second);
const Colour DarkKhaki = colourFromBGRA(__sourceColours[49].second);

// Green Colours
const Colour GreenYellow = colourFromBGRA(__sourceColours[50].second);
const Colour Chartreuse = colourFromBGRA(__sourceColours[51].second);
const Colour LawnGreen = colourFromBGRA(__sourceColours[52].second);
const Colour Lime = colourFromBGRA(__sourceColours[53].second);
const Colour LimeGreen = colourFromBGRA(__sourceColours[54].second);
const Colour PaleGreen = colourFromBGRA(__sourceColours[55].second);
const Colour LightGreen = colourFromBGRA(__sourceColours[56].second);
const Colour MediumSpringGreen = colourFromBGRA(__sourceColours[57].second);
const Colour SpringGreen = colourFromBGRA(__sourceColours[58].second);
const Colour MediumSeaGreen = colourFromBGRA(__sourceColours[59].second);
const Colour SeaGreen = colourFromBGRA(__sourceColours[60].second);
const Colour ForestGreen = colourFromBGRA(__sourceColours[61].second);
const Colour Green = colourFromBGRA(__sourceColours[62].second);
const Colour DarkGreen = colourFromBGRA(__sourceColours[63].second);
const Colour YellowGreen = colourFromBGRA(__sourceColours[64].second);
const Colour OliveDrab = colourFromBGRA(__sourceColours[65].second);
const Colour DarkOliveGreen = colourFromBGRA(__sourceColours[66].second);
const Colour MediumAquaMarine = colourFromBGRA(__sourceColours[67].second);
const Colour DarkSeaGreen = colourFromBGRA(__sourceColours[68].second);
const Colour LightSeaGreen = colourFromBGRA(__sourceColours[69].second);
const Colour DarkCyan = colourFromBGRA(__sourceColours[70].second);
const Colour Teal = colourFromBGRA(__sourceColours[71].second);

// Cyan Colours
const Colour Aqua = colourFromBGRA(__sourceColours[72].second);
const Colour Cyan = colourFromBGRA(__sourceColours[73].second);
const Colour LightCyan = colourFromBGRA(__sourceColours[74].second);
const Colour PaleTurquoise = colourFromBGRA(__sourceColours[75].second);
const Colour Aquamarine = colourFromBGRA(__sourceColours[76].second);
const Colour Turquoise = colourFromBGRA(__sourceColours[77].second);
const Colour MediumTurquoise = colourFromBGRA(__sourceColours[78].second);
const Colour DarkTurquoise = colourFromBGRA(__sourceColours[79].second);

// Blue Colours
const Colour CadetBlue = colourFromBGRA(__sourceColours[80].second);
const Colour SteelBlue = colourFromBGRA(__sourceColours[81].second);
const Colour LightSteelBlue = colourFromBGRA(__sourceColours[82].second);
const Colour LightBlue = colourFromBGRA(__sourceColours[83].second);
const Colour PowderBlue = colourFromBGRA(__sourceColours[84].second);
const Colour LightSkyBlue = colourFromBGRA(__sourceColours[85].second);
const Colour SkyBlue = colourFromBGRA(__sourceColours[86].second);
const Colour CornflowerBlue = colourFromBGRA(__sourceColours[87].second);
const Colour DeepSkyBlue = colourFromBGRA(__sourceColours[88].second);
const Colour DodgerBlue = colourFromBGRA(__sourceColours[89].second);
const Colour RoyalBlue = colourFromBGRA(__sourceColours[90].second);
const Colour Blue = colourFromBGRA(__sourceColours[91].second);
const Colour MediumBlue = colourFromBGRA(__sourceColours[92].second);
const Colour DarkBlue = colourFromBGRA(__sourceColours[93].second);
const Colour Navy = colourFromBGRA(__sourceColours[94].second);
const Colour MidnightBlue = colourFromBGRA(__sourceColours[95].second);

// Brown Colours
const Colour Cornsilk = colourFromBGRA(__sourceColours[96].second);
const Colour BlanchedAlmond = colourFromBGRA(__sourceColours[97].second);
const Colour Bisque = colourFromBGRA(__sourceColours[98].second);
const Colour NavajoWhite = colourFromBGRA(__sourceColours[99].second);
const Colour Wheat = colourFromBGRA(__sourceColours[100].second);
const Colour BurlyWood = colourFromBGRA(__sourceColours[101].second);
const Colour Tan = colourFromBGRA(__sourceColours[102].second);
const Colour RosyBrown = colourFromBGRA(__sourceColours[103].second);
const Colour SandyBrown = colourFromBGRA(__sourceColours[104].second);
const Colour GoldenRod = colourFromBGRA(__sourceColours[105].second);
const Colour DarkGoldenRod = colourFromBGRA(__sourceColours[106].second);
const Colour Peru = colourFromBGRA(__sourceColours[107].second);
const Colour Chocolate = colourFromBGRA(__sourceColours[108].second);
const Colour Olive = colourFromBGRA(__sourceColours[109].second);
const Colour SaddleBrown = colourFromBGRA(__sourceColours[110].second);
const Colour Sienna = colourFromBGRA(__sourceColours[111].second);
const Colour Brown = colourFromBGRA(__sourceColours[112].second);
const Colour Maroon = colourFromBGRA(__sourceColours[113].second);

// White Colours
const Colour White = colourFromBGRA(__sourceColours[114].second);
const Colour Snow = colourFromBGRA(__sourceColours[115].second);
const Colour HoneyDew = colourFromBGRA(__sourceColours[116].second);
const Colour MintCream = colourFromBGRA(__sourceColours[117].second);
const Colour Azure = colourFromBGRA(__sourceColours[118].second);
const Colour AliceBlue = colourFromBGRA(__sourceColours[119].second);
const Colour GhostWhite = colourFromBGRA(__sourceColours[120].second);
const Colour WhiteSmoke = colourFromBGRA(__sourceColours[121].second);
const Colour SeaShell = colourFromBGRA(__sourceColours[122].second);
const Colour Beige = colourFromBGRA(__sourceColours[123].second);
const Colour OldLace = colourFromBGRA(__sourceColours[124].second);
const Colour FloralWhite = colourFromBGRA(__sourceColours[125].second);
const Colour Ivory = colourFromBGRA(__sourceColours[126].second);
const Colour AntiqueWhite = colourFromBGRA(__sourceColours[127].second);
const Colour Linen = colourFromBGRA(__sourceColours[128].second);
const Colour LavenderBlush = colourFromBGRA(__sourceColours[129].second);
const Colour MistyRose = colourFromBGRA(__sourceColours[130].second);

// Grey Colours
const Colour Gainsboro = colourFromBGRA(__sourceColours[131].second);
const Colour LightGray = colourFromBGRA(__sourceColours[132].second);
const Colour Silver = colourFromBGRA(__sourceColours[133].second);
const Colour DarkGray = colourFromBGRA(__sourceColours[134].second);
const Colour DimGray = colourFromBGRA(__sourceColours[135].second);
const Colour Gray = colourFromBGRA(__sourceColours[136].second);
const Colour LightSlateGray = colourFromBGRA(__sourceColours[137].second);
const Colour SlateGray = colourFromBGRA(__sourceColours[138].second);
const Colour DarkSlateGray = colourFromBGRA(__sourceColours[139].second);
const Colour Black = colourFromBGRA(__sourceColours[140].second);

// Misc. Colours
const Colour Transparent = colourFromBGRA(__sourceColours[141].second);

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the count of named colours.
Index getNamedColourCount()
{
    return static_cast<Index>(std::size(__sourceColours));
}

//! @brief Gets the display name of a named colour.
//! @param[in] index The 0-based index of the colour.
//! @return The colour name.
//! @throws IndexOutOfRangeException if index is invalid.
string_cref_t getDisplayName(Index index)
{
    const NamedColour *colours = getNamedColours();

    if (index < std::size(__sourceColours))
    {
        return colours[index].DisplayName;
    }
    else
    {
        throw IndexOutOfRangeException(static_cast<size_t>(index),
                                       std::size(__sourceColours));
    }
}

//! @brief Gets the value of a named colour.
//! @param[in] index The 0-based index of the colour.
//! @return The colour value.
//! @throws IndexOutOfRangeException if index is invalid.
const Colour &getValue(Index index)
{
    const NamedColour *colours = getNamedColours();

    if (index < std::size(__sourceColours))
    {
        return colours[index].Value;
    }
    else
    {
        throw IndexOutOfRangeException(static_cast<size_t>(index),
                                       std::size(__sourceColours));
    }
}

//! @brief Attempts to find a colour by its name.
//! @param[in] name The case-insensitive name to search by.
//! @param[out] index Receives the index of the matching colour, if one
//! was found.
//! @retval true A colour matching the name was found and its index
//! was returned in @p index.
//! @retval false No colour matched the name.
bool tryGetColourByName(string_cref_t name, Index &index)
{
    index = static_cast<Index>(std::size(__sourceColours));
    getNamedColours();

    String key = name.toUpper();

    auto pos = __colourIndexByNameKey.find(key);

    if (pos != __colourIndexByNameKey.end())
    {
        index = pos->second;
        return true;
    }

    return false;
}

//! @brief Attempts to match a named colour to a raw RGBA value.
//! @param[out] index Receives the index of the matching colour.
//! @param[in] red The 8-bit red component of the colour to match.
//! @param[in] green The 8-bit green component of the colour to match.
//! @param[in] blue The 8-bit blue component of the colour to match.
//! @param[in] alpha The 8-bit alpha transparency component of the colour to match.
//! @retval true A colour matching the value was found and its index returned.
//! @retval false No colour matched the specified components.
bool tryGetColourByValue(Index &index, uint8_t red, uint8_t green,
                         uint8_t blue, uint8_t alpha /*= 0xFF*/)
{
    index = static_cast<Index>(std::size(__sourceColours));

    uint32_t rawColour = static_cast<uint32_t>(blue) |
                         (static_cast<uint32_t>(green) << 8) |
                         (static_cast<uint32_t>(red) << 16) |
                         (static_cast<uint32_t>(alpha) << 24);

    getNamedColours();
    size_t mappingIndex;

    if (__colourIndexByRawColour.tryFindValue(rawColour, mappingIndex))
    {
        index = __colourIndexByRawColour.getValue(mappingIndex);
        return true;
    }

    return false;
}

}}} // namespace Ag::Gfx2D::Colours
////////////////////////////////////////////////////////////////////////////////

