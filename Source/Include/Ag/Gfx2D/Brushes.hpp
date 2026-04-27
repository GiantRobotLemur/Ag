//! @file Ag/Gfx2D/Brushes.hpp
//! @brief The declaration of static solid colour brushes representing
//! named colours.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_BRUSHES_HPP__
#define __GFX_2D_BRUSHES_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Brush.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A static class defining solid brushes that correspond to the members
//! of the Colours namespace.
struct Brushes
{
    // Ensure no instances of the class are possible.
    Brushes() = delete;
    ~Brushes() = delete;

    // Public Data
    static const SolidColourBrushSPtr Pink;
    static const SolidColourBrushSPtr LightPink;
    static const SolidColourBrushSPtr HotPink;
    static const SolidColourBrushSPtr DeepPink;
    static const SolidColourBrushSPtr PaleVioletRed;
    static const SolidColourBrushSPtr MediumVioletRed;

    // Purple Colours
    static const SolidColourBrushSPtr Lavender;
    static const SolidColourBrushSPtr Thistle;
    static const SolidColourBrushSPtr Plum;
    static const SolidColourBrushSPtr Orchid;
    static const SolidColourBrushSPtr Violet;
    static const SolidColourBrushSPtr Fuchsia;
    static const SolidColourBrushSPtr Magenta;
    static const SolidColourBrushSPtr MediumOrchid;
    static const SolidColourBrushSPtr DarkOrchid;
    static const SolidColourBrushSPtr DarkViolet;
    static const SolidColourBrushSPtr BlueViolet;
    static const SolidColourBrushSPtr DarkMagenta;
    static const SolidColourBrushSPtr Purple;
    static const SolidColourBrushSPtr MediumPurple;
    static const SolidColourBrushSPtr MediumSlateBlue;
    static const SolidColourBrushSPtr SlateBlue;
    static const SolidColourBrushSPtr DarkSlateBlue;
    static const SolidColourBrushSPtr RebeccaPurple;
    static const SolidColourBrushSPtr Indigo;

    // Red Colours
    static const SolidColourBrushSPtr LightSalmon;
    static const SolidColourBrushSPtr Salmon;
    static const SolidColourBrushSPtr DarkSalmon;
    static const SolidColourBrushSPtr LightCoral;
    static const SolidColourBrushSPtr IndianRed;
    static const SolidColourBrushSPtr Crimson;
    static const SolidColourBrushSPtr Red;
    static const SolidColourBrushSPtr FireBrick;
    static const SolidColourBrushSPtr DarkRed;

    // Orange Colours
    static const SolidColourBrushSPtr Orange;
    static const SolidColourBrushSPtr DarkOrange;
    static const SolidColourBrushSPtr Coral;
    static const SolidColourBrushSPtr Tomato;
    static const SolidColourBrushSPtr OrangeRed;

    // Yellow Colours
    static const SolidColourBrushSPtr Gold;
    static const SolidColourBrushSPtr Yellow;
    static const SolidColourBrushSPtr LightYellow;
    static const SolidColourBrushSPtr LemonChiffon;
    static const SolidColourBrushSPtr LightGoldenRodYellow;
    static const SolidColourBrushSPtr PapayaWhip;
    static const SolidColourBrushSPtr Moccasin;
    static const SolidColourBrushSPtr PeachPuff;
    static const SolidColourBrushSPtr PaleGoldenRod;
    static const SolidColourBrushSPtr Khaki;
    static const SolidColourBrushSPtr DarkKhaki;

    // Green Colours
    static const SolidColourBrushSPtr GreenYellow;
    static const SolidColourBrushSPtr Chartreuse;
    static const SolidColourBrushSPtr LawnGreen;
    static const SolidColourBrushSPtr Lime;
    static const SolidColourBrushSPtr LimeGreen;
    static const SolidColourBrushSPtr PaleGreen;
    static const SolidColourBrushSPtr LightGreen;
    static const SolidColourBrushSPtr MediumSpringGreen;
    static const SolidColourBrushSPtr SpringGreen;
    static const SolidColourBrushSPtr MediumSeaGreen;
    static const SolidColourBrushSPtr SeaGreen;
    static const SolidColourBrushSPtr ForestGreen;
    static const SolidColourBrushSPtr Green;
    static const SolidColourBrushSPtr DarkGreen;
    static const SolidColourBrushSPtr YellowGreen;
    static const SolidColourBrushSPtr OliveDrab;
    static const SolidColourBrushSPtr DarkOliveGreen;
    static const SolidColourBrushSPtr MediumAquaMarine;
    static const SolidColourBrushSPtr DarkSeaGreen;
    static const SolidColourBrushSPtr LightSeaGreen;
    static const SolidColourBrushSPtr DarkCyan;
    static const SolidColourBrushSPtr Teal;

    // Cyan Colours
    static const SolidColourBrushSPtr Aqua;
    static const SolidColourBrushSPtr Cyan;
    static const SolidColourBrushSPtr LightCyan;
    static const SolidColourBrushSPtr PaleTurquoise;
    static const SolidColourBrushSPtr Aquamarine;
    static const SolidColourBrushSPtr Turquoise;
    static const SolidColourBrushSPtr MediumTurquoise;
    static const SolidColourBrushSPtr DarkTurquoise;

    // Blue Colours
    static const SolidColourBrushSPtr CadetBlue;
    static const SolidColourBrushSPtr SteelBlue;
    static const SolidColourBrushSPtr LightSteelBlue;
    static const SolidColourBrushSPtr LightBlue;
    static const SolidColourBrushSPtr PowderBlue;
    static const SolidColourBrushSPtr LightSkyBlue;
    static const SolidColourBrushSPtr SkyBlue;
    static const SolidColourBrushSPtr CornflowerBlue;
    static const SolidColourBrushSPtr DeepSkyBlue;
    static const SolidColourBrushSPtr DodgerBlue;
    static const SolidColourBrushSPtr RoyalBlue;
    static const SolidColourBrushSPtr Blue;
    static const SolidColourBrushSPtr MediumBlue;
    static const SolidColourBrushSPtr DarkBlue;
    static const SolidColourBrushSPtr Navy;
    static const SolidColourBrushSPtr MidnightBlue;

    // Brown Colours
    static const SolidColourBrushSPtr Cornsilk;
    static const SolidColourBrushSPtr BlanchedAlmond;
    static const SolidColourBrushSPtr Bisque;
    static const SolidColourBrushSPtr NavajoWhite;
    static const SolidColourBrushSPtr Wheat;
    static const SolidColourBrushSPtr BurlyWood;
    static const SolidColourBrushSPtr Tan;
    static const SolidColourBrushSPtr RosyBrown;
    static const SolidColourBrushSPtr SandyBrown;
    static const SolidColourBrushSPtr GoldenRod;
    static const SolidColourBrushSPtr DarkGoldenRod;
    static const SolidColourBrushSPtr Peru;
    static const SolidColourBrushSPtr Chocolate;
    static const SolidColourBrushSPtr Olive;
    static const SolidColourBrushSPtr SaddleBrown;
    static const SolidColourBrushSPtr Sienna;
    static const SolidColourBrushSPtr Brown;
    static const SolidColourBrushSPtr Maroon;

    // White Colours
    static const SolidColourBrushSPtr White;
    static const SolidColourBrushSPtr Snow;
    static const SolidColourBrushSPtr HoneyDew;
    static const SolidColourBrushSPtr MintCream;
    static const SolidColourBrushSPtr Azure;
    static const SolidColourBrushSPtr AliceBlue;
    static const SolidColourBrushSPtr GhostWhite;
    static const SolidColourBrushSPtr WhiteSmoke;
    static const SolidColourBrushSPtr SeaShell;
    static const SolidColourBrushSPtr Beige;
    static const SolidColourBrushSPtr OldLace;
    static const SolidColourBrushSPtr FloralWhite;
    static const SolidColourBrushSPtr Ivory;
    static const SolidColourBrushSPtr AntiqueWhite;
    static const SolidColourBrushSPtr Linen;
    static const SolidColourBrushSPtr LavenderBlush;
    static const SolidColourBrushSPtr MistyRose;

    // Grey Colours
    static const SolidColourBrushSPtr Gainsboro;
    static const SolidColourBrushSPtr LightGray;
    static const SolidColourBrushSPtr Silver;
    static const SolidColourBrushSPtr DarkGray;
    static const SolidColourBrushSPtr DimGray;
    static const SolidColourBrushSPtr Gray;
    static const SolidColourBrushSPtr LightSlateGray;
    static const SolidColourBrushSPtr SlateGray;
    static const SolidColourBrushSPtr DarkSlateGray;
    static const SolidColourBrushSPtr Black;

    // Misc Colours
    static const SolidColourBrushSPtr Transparent;

    // Public Types
    //using Index = uint8_t;

    //// Accessors
    //static Index getNamedBrushCount();
    //static SolidColourBrushSPtr getBrush(Index index);

    //static bool tryGetBrushByName(string_cref_t name, Index &index);
    //static bool tryGetBrushByValue(Index &index, uint8_t red, uint8_t green,
    //                               uint8_t blue, uint8_t alpha = 0xFF);
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
