//! @file Ag/Gfx2D/Colours.hpp
//! @brief The declaration of a static set of named colours.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_COLOURS_HPP__
#define __GFX_2D_COLOURS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Colour.hpp"

namespace Ag {
namespace Gfx2D {

//! @brief A static set of named colours.
namespace Colours {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
using Index = uint8_t;

////////////////////////////////////////////////////////////////////////////////
// Data Declarations
////////////////////////////////////////////////////////////////////////////////
// Pink Colours
extern const Colour Pink;
extern const Colour LightPink;
extern const Colour HotPink;
extern const Colour DeepPink;
extern const Colour PaleVioletRed;
extern const Colour MediumVioletRed;

// Purple Colours
extern const Colour Lavender;
extern const Colour Thistle;
extern const Colour Plum;
extern const Colour Orchid;
extern const Colour Violet;
extern const Colour Fuchsia;
extern const Colour Magenta;
extern const Colour MediumOrchid;
extern const Colour DarkOrchid;
extern const Colour DarkViolet;
extern const Colour BlueViolet;
extern const Colour DarkMagenta;
extern const Colour Purple;
extern const Colour MediumPurple;
extern const Colour MediumSlateBlue;
extern const Colour SlateBlue;
extern const Colour DarkSlateBlue;
extern const Colour RebeccaPurple;
extern const Colour Indigo;

// Red Colours
extern const Colour LightSalmon;
extern const Colour Salmon;
extern const Colour DarkSalmon;
extern const Colour LightCoral;
extern const Colour IndianRed;
extern const Colour Crimson;
extern const Colour Red;
extern const Colour FireBrick;
extern const Colour DarkRed;

// Orange Colours
extern const Colour Orange;
extern const Colour DarkOrange;
extern const Colour Coral;
extern const Colour Tomato;
extern const Colour OrangeRed;

// Yellow Colours
extern const Colour Gold;
extern const Colour Yellow;
extern const Colour LightYellow;
extern const Colour LemonChiffon;
extern const Colour LightGoldenRodYellow;
extern const Colour PapayaWhip;
extern const Colour Moccasin;
extern const Colour PeachPuff;
extern const Colour PaleGoldenRod;
extern const Colour Khaki;
extern const Colour DarkKhaki;

// Green Colours
extern const Colour GreenYellow;
extern const Colour Chartreuse;
extern const Colour LawnGreen;
extern const Colour Lime;
extern const Colour LimeGreen;
extern const Colour PaleGreen;
extern const Colour LightGreen;
extern const Colour MediumSpringGreen;
extern const Colour SpringGreen;
extern const Colour MediumSeaGreen;
extern const Colour SeaGreen;
extern const Colour ForestGreen;
extern const Colour Green;
extern const Colour DarkGreen;
extern const Colour YellowGreen;
extern const Colour OliveDrab;
extern const Colour DarkOliveGreen;
extern const Colour MediumAquaMarine;
extern const Colour DarkSeaGreen;
extern const Colour LightSeaGreen;
extern const Colour DarkCyan;
extern const Colour Teal;

// Cyan Colours
extern const Colour Aqua;
extern const Colour Cyan;
extern const Colour LightCyan;
extern const Colour PaleTurquoise;
extern const Colour Aquamarine;
extern const Colour Turquoise;
extern const Colour MediumTurquoise;
extern const Colour DarkTurquoise;

// Blue Colours
extern const Colour CadetBlue;
extern const Colour SteelBlue;
extern const Colour LightSteelBlue;
extern const Colour LightBlue;
extern const Colour PowderBlue;
extern const Colour LightSkyBlue;
extern const Colour SkyBlue;
extern const Colour CornflowerBlue;
extern const Colour DeepSkyBlue;
extern const Colour DodgerBlue;
extern const Colour RoyalBlue;
extern const Colour Blue;
extern const Colour MediumBlue;
extern const Colour DarkBlue;
extern const Colour Navy;
extern const Colour MidnightBlue;

// Brown Colours
extern const Colour Cornsilk;
extern const Colour BlanchedAlmond;
extern const Colour Bisque;
extern const Colour NavajoWhite;
extern const Colour Wheat;
extern const Colour BurlyWood;
extern const Colour Tan;
extern const Colour RosyBrown;
extern const Colour SandyBrown;
extern const Colour GoldenRod;
extern const Colour DarkGoldenRod;
extern const Colour Peru;
extern const Colour Chocolate;
extern const Colour Olive;
extern const Colour SaddleBrown;
extern const Colour Sienna;
extern const Colour Brown;
extern const Colour Maroon;

// White Colours
extern const Colour White;
extern const Colour Snow;
extern const Colour HoneyDew;
extern const Colour MintCream;
extern const Colour Azure;
extern const Colour AliceBlue;
extern const Colour GhostWhite;
extern const Colour WhiteSmoke;
extern const Colour SeaShell;
extern const Colour Beige;
extern const Colour OldLace;
extern const Colour FloralWhite;
extern const Colour Ivory;
extern const Colour AntiqueWhite;
extern const Colour Linen;
extern const Colour LavenderBlush;
extern const Colour MistyRose;

// Grey Colours
extern const Colour Gainsboro;
extern const Colour LightGray;
extern const Colour Silver;
extern const Colour DarkGray;
extern const Colour DimGray;
extern const Colour Gray;
extern const Colour LightSlateGray;
extern const Colour SlateGray;
extern const Colour DarkSlateGray;
extern const Colour Black;

// Misc Colours
extern const Colour Transparent;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
Index getNamedColourCount();
string_cref_t getDisplayName(Index index);
const Colour &getValue(Index index);

bool tryGetColourByName(string_cref_t name, Index &index);
bool tryGetColourByValue(Index &index, uint8_t red, uint8_t green,
                         uint8_t blue, uint8_t alpha = 0xFF);

}}} // namespace Ag::Gfx2D::Colours

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
