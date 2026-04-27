//! @file Gfx2D/Brushes.cpp
//! @brief The definition of static solid colour brushes representing
//! named colours.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/Brushes.hpp"
#include "Ag/Gfx2D/Colours.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Brushes Member Definitions
////////////////////////////////////////////////////////////////////////////////
const SolidColourBrushSPtr Brushes::Pink(std::make_shared<SolidColourBrush>(Colours::Pink, true));
const SolidColourBrushSPtr Brushes::LightPink(std::make_shared<SolidColourBrush>(Colours::LightPink, true));
const SolidColourBrushSPtr Brushes::HotPink(std::make_shared<SolidColourBrush>(Colours::HotPink, true));
const SolidColourBrushSPtr Brushes::DeepPink(std::make_shared<SolidColourBrush>(Colours::DeepPink, true));
const SolidColourBrushSPtr Brushes::PaleVioletRed(std::make_shared<SolidColourBrush>(Colours::PaleVioletRed, true));
const SolidColourBrushSPtr Brushes::MediumVioletRed(std::make_shared<SolidColourBrush>(Colours::MediumVioletRed, true));

// Purple Colours
const SolidColourBrushSPtr Brushes::Lavender(std::make_shared<SolidColourBrush>(Colours::Lavender, true));
const SolidColourBrushSPtr Brushes::Thistle(std::make_shared<SolidColourBrush>(Colours::Thistle, true));
const SolidColourBrushSPtr Brushes::Plum(std::make_shared<SolidColourBrush>(Colours::Plum, true));
const SolidColourBrushSPtr Brushes::Orchid(std::make_shared<SolidColourBrush>(Colours::Orchid, true));
const SolidColourBrushSPtr Brushes::Violet(std::make_shared<SolidColourBrush>(Colours::Violet, true));
const SolidColourBrushSPtr Brushes::Fuchsia(std::make_shared<SolidColourBrush>(Colours::Fuchsia, true));
const SolidColourBrushSPtr Brushes::Magenta(std::make_shared<SolidColourBrush>(Colours::Magenta, true));
const SolidColourBrushSPtr Brushes::MediumOrchid(std::make_shared<SolidColourBrush>(Colours::MediumOrchid, true));
const SolidColourBrushSPtr Brushes::DarkOrchid(std::make_shared<SolidColourBrush>(Colours::DarkOrchid, true));
const SolidColourBrushSPtr Brushes::DarkViolet(std::make_shared<SolidColourBrush>(Colours::DarkViolet, true));
const SolidColourBrushSPtr Brushes::BlueViolet(std::make_shared<SolidColourBrush>(Colours::BlueViolet, true));
const SolidColourBrushSPtr Brushes::DarkMagenta(std::make_shared<SolidColourBrush>(Colours::DarkMagenta, true));
const SolidColourBrushSPtr Brushes::Purple(std::make_shared<SolidColourBrush>(Colours::Purple, true));
const SolidColourBrushSPtr Brushes::MediumPurple(std::make_shared<SolidColourBrush>(Colours::MediumPurple, true));
const SolidColourBrushSPtr Brushes::MediumSlateBlue(std::make_shared<SolidColourBrush>(Colours::MediumSlateBlue, true));
const SolidColourBrushSPtr Brushes::SlateBlue(std::make_shared<SolidColourBrush>(Colours::SlateBlue, true));
const SolidColourBrushSPtr Brushes::DarkSlateBlue(std::make_shared<SolidColourBrush>(Colours::DarkSlateBlue, true));
const SolidColourBrushSPtr Brushes::RebeccaPurple(std::make_shared<SolidColourBrush>(Colours::RebeccaPurple, true));
const SolidColourBrushSPtr Brushes::Indigo(std::make_shared<SolidColourBrush>(Colours::Indigo, true));

// Red Colours
const SolidColourBrushSPtr Brushes::LightSalmon(std::make_shared<SolidColourBrush>(Colours::LightSalmon, true));
const SolidColourBrushSPtr Brushes::Salmon(std::make_shared<SolidColourBrush>(Colours::Salmon, true));
const SolidColourBrushSPtr Brushes::DarkSalmon(std::make_shared<SolidColourBrush>(Colours::DarkSalmon, true));
const SolidColourBrushSPtr Brushes::LightCoral(std::make_shared<SolidColourBrush>(Colours::LightCoral, true));
const SolidColourBrushSPtr Brushes::IndianRed(std::make_shared<SolidColourBrush>(Colours::IndianRed, true));
const SolidColourBrushSPtr Brushes::Crimson(std::make_shared<SolidColourBrush>(Colours::Crimson, true));
const SolidColourBrushSPtr Brushes::Red(std::make_shared<SolidColourBrush>(Colours::Red, true));
const SolidColourBrushSPtr Brushes::FireBrick(std::make_shared<SolidColourBrush>(Colours::FireBrick, true));
const SolidColourBrushSPtr Brushes::DarkRed(std::make_shared<SolidColourBrush>(Colours::DarkRed, true));

// Orange Colours
const SolidColourBrushSPtr Brushes::Orange(std::make_shared<SolidColourBrush>(Colours::Orange, true));
const SolidColourBrushSPtr Brushes::DarkOrange(std::make_shared<SolidColourBrush>(Colours::DarkOrange, true));
const SolidColourBrushSPtr Brushes::Coral(std::make_shared<SolidColourBrush>(Colours::Coral, true));
const SolidColourBrushSPtr Brushes::Tomato(std::make_shared<SolidColourBrush>(Colours::Tomato, true));
const SolidColourBrushSPtr Brushes::OrangeRed(std::make_shared<SolidColourBrush>(Colours::OrangeRed, true));

// Yellow Colours
const SolidColourBrushSPtr Brushes::Gold(std::make_shared<SolidColourBrush>(Colours::Gold, true));
const SolidColourBrushSPtr Brushes::Yellow(std::make_shared<SolidColourBrush>(Colours::Yellow, true));
const SolidColourBrushSPtr Brushes::LightYellow(std::make_shared<SolidColourBrush>(Colours::LightYellow, true));
const SolidColourBrushSPtr Brushes::LemonChiffon(std::make_shared<SolidColourBrush>(Colours::LemonChiffon, true));
const SolidColourBrushSPtr Brushes::LightGoldenRodYellow(std::make_shared<SolidColourBrush>(Colours::LightGoldenRodYellow, true));
const SolidColourBrushSPtr Brushes::PapayaWhip(std::make_shared<SolidColourBrush>(Colours::PapayaWhip, true));
const SolidColourBrushSPtr Brushes::Moccasin(std::make_shared<SolidColourBrush>(Colours::Moccasin, true));
const SolidColourBrushSPtr Brushes::PeachPuff(std::make_shared<SolidColourBrush>(Colours::PeachPuff, true));
const SolidColourBrushSPtr Brushes::PaleGoldenRod(std::make_shared<SolidColourBrush>(Colours::PaleGoldenRod, true));
const SolidColourBrushSPtr Brushes::Khaki(std::make_shared<SolidColourBrush>(Colours::Khaki, true));
const SolidColourBrushSPtr Brushes::DarkKhaki(std::make_shared<SolidColourBrush>(Colours::DarkKhaki, true));

// Green Colours
const SolidColourBrushSPtr Brushes::GreenYellow(std::make_shared<SolidColourBrush>(Colours::GreenYellow, true));
const SolidColourBrushSPtr Brushes::Chartreuse(std::make_shared<SolidColourBrush>(Colours::Chartreuse, true));
const SolidColourBrushSPtr Brushes::LawnGreen(std::make_shared<SolidColourBrush>(Colours::LawnGreen, true));
const SolidColourBrushSPtr Brushes::Lime(std::make_shared<SolidColourBrush>(Colours::Lime, true));
const SolidColourBrushSPtr Brushes::LimeGreen(std::make_shared<SolidColourBrush>(Colours::LimeGreen, true));
const SolidColourBrushSPtr Brushes::PaleGreen(std::make_shared<SolidColourBrush>(Colours::PaleGreen, true));
const SolidColourBrushSPtr Brushes::LightGreen(std::make_shared<SolidColourBrush>(Colours::LightGreen, true));
const SolidColourBrushSPtr Brushes::MediumSpringGreen(std::make_shared<SolidColourBrush>(Colours::MediumSpringGreen, true));
const SolidColourBrushSPtr Brushes::SpringGreen(std::make_shared<SolidColourBrush>(Colours::SpringGreen, true));
const SolidColourBrushSPtr Brushes::MediumSeaGreen(std::make_shared<SolidColourBrush>(Colours::MediumSeaGreen, true));
const SolidColourBrushSPtr Brushes::SeaGreen(std::make_shared<SolidColourBrush>(Colours::SeaGreen, true));
const SolidColourBrushSPtr Brushes::ForestGreen(std::make_shared<SolidColourBrush>(Colours::ForestGreen, true));
const SolidColourBrushSPtr Brushes::Green(std::make_shared<SolidColourBrush>(Colours::Green, true));
const SolidColourBrushSPtr Brushes::DarkGreen(std::make_shared<SolidColourBrush>(Colours::DarkGreen, true));
const SolidColourBrushSPtr Brushes::YellowGreen(std::make_shared<SolidColourBrush>(Colours::YellowGreen, true));
const SolidColourBrushSPtr Brushes::OliveDrab(std::make_shared<SolidColourBrush>(Colours::OliveDrab, true));
const SolidColourBrushSPtr Brushes::DarkOliveGreen(std::make_shared<SolidColourBrush>(Colours::DarkOliveGreen, true));
const SolidColourBrushSPtr Brushes::MediumAquaMarine(std::make_shared<SolidColourBrush>(Colours::MediumAquaMarine, true));
const SolidColourBrushSPtr Brushes::DarkSeaGreen(std::make_shared<SolidColourBrush>(Colours::DarkSeaGreen, true));
const SolidColourBrushSPtr Brushes::LightSeaGreen(std::make_shared<SolidColourBrush>(Colours::LightSeaGreen, true));
const SolidColourBrushSPtr Brushes::DarkCyan(std::make_shared<SolidColourBrush>(Colours::DarkCyan, true));
const SolidColourBrushSPtr Brushes::Teal(std::make_shared<SolidColourBrush>(Colours::Teal, true));

// Cyan Colours
const SolidColourBrushSPtr Brushes::Aqua(std::make_shared<SolidColourBrush>(Colours::Aqua, true));
const SolidColourBrushSPtr Brushes::Cyan(std::make_shared<SolidColourBrush>(Colours::Cyan, true));
const SolidColourBrushSPtr Brushes::LightCyan(std::make_shared<SolidColourBrush>(Colours::LightCyan, true));
const SolidColourBrushSPtr Brushes::PaleTurquoise(std::make_shared<SolidColourBrush>(Colours::PaleTurquoise, true));
const SolidColourBrushSPtr Brushes::Aquamarine(std::make_shared<SolidColourBrush>(Colours::Aquamarine, true));
const SolidColourBrushSPtr Brushes::Turquoise(std::make_shared<SolidColourBrush>(Colours::Turquoise, true));
const SolidColourBrushSPtr Brushes::MediumTurquoise(std::make_shared<SolidColourBrush>(Colours::MediumTurquoise, true));
const SolidColourBrushSPtr Brushes::DarkTurquoise(std::make_shared<SolidColourBrush>(Colours::DarkTurquoise, true));

// Blue Colours
const SolidColourBrushSPtr Brushes::CadetBlue(std::make_shared<SolidColourBrush>(Colours::CadetBlue, true));
const SolidColourBrushSPtr Brushes::SteelBlue(std::make_shared<SolidColourBrush>(Colours::SteelBlue, true));
const SolidColourBrushSPtr Brushes::LightSteelBlue(std::make_shared<SolidColourBrush>(Colours::LightSteelBlue, true));
const SolidColourBrushSPtr Brushes::LightBlue(std::make_shared<SolidColourBrush>(Colours::LightBlue, true));
const SolidColourBrushSPtr Brushes::PowderBlue(std::make_shared<SolidColourBrush>(Colours::PowderBlue, true));
const SolidColourBrushSPtr Brushes::LightSkyBlue(std::make_shared<SolidColourBrush>(Colours::LightSkyBlue, true));
const SolidColourBrushSPtr Brushes::SkyBlue(std::make_shared<SolidColourBrush>(Colours::SkyBlue, true));
const SolidColourBrushSPtr Brushes::CornflowerBlue(std::make_shared<SolidColourBrush>(Colours::CornflowerBlue, true));
const SolidColourBrushSPtr Brushes::DeepSkyBlue(std::make_shared<SolidColourBrush>(Colours::DeepSkyBlue, true));
const SolidColourBrushSPtr Brushes::DodgerBlue(std::make_shared<SolidColourBrush>(Colours::DodgerBlue, true));
const SolidColourBrushSPtr Brushes::RoyalBlue(std::make_shared<SolidColourBrush>(Colours::RoyalBlue, true));
const SolidColourBrushSPtr Brushes::Blue(std::make_shared<SolidColourBrush>(Colours::Blue, true));
const SolidColourBrushSPtr Brushes::MediumBlue(std::make_shared<SolidColourBrush>(Colours::MediumBlue, true));
const SolidColourBrushSPtr Brushes::DarkBlue(std::make_shared<SolidColourBrush>(Colours::DarkBlue, true));
const SolidColourBrushSPtr Brushes::Navy(std::make_shared<SolidColourBrush>(Colours::Navy, true));
const SolidColourBrushSPtr Brushes::MidnightBlue(std::make_shared<SolidColourBrush>(Colours::MidnightBlue, true));

// Brown Colours
const SolidColourBrushSPtr Brushes::Cornsilk(std::make_shared<SolidColourBrush>(Colours::Cornsilk, true));
const SolidColourBrushSPtr Brushes::BlanchedAlmond(std::make_shared<SolidColourBrush>(Colours::BlanchedAlmond, true));
const SolidColourBrushSPtr Brushes::Bisque(std::make_shared<SolidColourBrush>(Colours::Bisque, true));
const SolidColourBrushSPtr Brushes::NavajoWhite(std::make_shared<SolidColourBrush>(Colours::NavajoWhite, true));
const SolidColourBrushSPtr Brushes::Wheat(std::make_shared<SolidColourBrush>(Colours::Wheat, true));
const SolidColourBrushSPtr Brushes::BurlyWood(std::make_shared<SolidColourBrush>(Colours::BurlyWood, true));
const SolidColourBrushSPtr Brushes::Tan(std::make_shared<SolidColourBrush>(Colours::Tan, true));
const SolidColourBrushSPtr Brushes::RosyBrown(std::make_shared<SolidColourBrush>(Colours::RosyBrown, true));
const SolidColourBrushSPtr Brushes::SandyBrown(std::make_shared<SolidColourBrush>(Colours::SandyBrown, true));
const SolidColourBrushSPtr Brushes::GoldenRod(std::make_shared<SolidColourBrush>(Colours::GoldenRod, true));
const SolidColourBrushSPtr Brushes::DarkGoldenRod(std::make_shared<SolidColourBrush>(Colours::DarkGoldenRod, true));
const SolidColourBrushSPtr Brushes::Peru(std::make_shared<SolidColourBrush>(Colours::Peru, true));
const SolidColourBrushSPtr Brushes::Chocolate(std::make_shared<SolidColourBrush>(Colours::Chocolate, true));
const SolidColourBrushSPtr Brushes::Olive(std::make_shared<SolidColourBrush>(Colours::Olive, true));
const SolidColourBrushSPtr Brushes::SaddleBrown(std::make_shared<SolidColourBrush>(Colours::SaddleBrown, true));
const SolidColourBrushSPtr Brushes::Sienna(std::make_shared<SolidColourBrush>(Colours::Sienna, true));
const SolidColourBrushSPtr Brushes::Brown(std::make_shared<SolidColourBrush>(Colours::Brown, true));
const SolidColourBrushSPtr Brushes::Maroon(std::make_shared<SolidColourBrush>(Colours::Maroon, true));

// White Colours
const SolidColourBrushSPtr Brushes::White(std::make_shared<SolidColourBrush>(Colours::White, true));
const SolidColourBrushSPtr Brushes::Snow(std::make_shared<SolidColourBrush>(Colours::Snow, true));
const SolidColourBrushSPtr Brushes::HoneyDew(std::make_shared<SolidColourBrush>(Colours::HoneyDew, true));
const SolidColourBrushSPtr Brushes::MintCream(std::make_shared<SolidColourBrush>(Colours::MintCream, true));
const SolidColourBrushSPtr Brushes::Azure(std::make_shared<SolidColourBrush>(Colours::Azure, true));
const SolidColourBrushSPtr Brushes::AliceBlue(std::make_shared<SolidColourBrush>(Colours::AliceBlue, true));
const SolidColourBrushSPtr Brushes::GhostWhite(std::make_shared<SolidColourBrush>(Colours::GhostWhite, true));
const SolidColourBrushSPtr Brushes::WhiteSmoke(std::make_shared<SolidColourBrush>(Colours::WhiteSmoke, true));
const SolidColourBrushSPtr Brushes::SeaShell(std::make_shared<SolidColourBrush>(Colours::SeaShell, true));
const SolidColourBrushSPtr Brushes::Beige(std::make_shared<SolidColourBrush>(Colours::Beige, true));
const SolidColourBrushSPtr Brushes::OldLace(std::make_shared<SolidColourBrush>(Colours::OldLace, true));
const SolidColourBrushSPtr Brushes::FloralWhite(std::make_shared<SolidColourBrush>(Colours::FloralWhite, true));
const SolidColourBrushSPtr Brushes::Ivory(std::make_shared<SolidColourBrush>(Colours::Ivory, true));
const SolidColourBrushSPtr Brushes::AntiqueWhite(std::make_shared<SolidColourBrush>(Colours::AntiqueWhite, true));
const SolidColourBrushSPtr Brushes::Linen(std::make_shared<SolidColourBrush>(Colours::Linen, true));
const SolidColourBrushSPtr Brushes::LavenderBlush(std::make_shared<SolidColourBrush>(Colours::LavenderBlush, true));
const SolidColourBrushSPtr Brushes::MistyRose(std::make_shared<SolidColourBrush>(Colours::MistyRose, true));

// Grey Colours
const SolidColourBrushSPtr Brushes::Gainsboro(std::make_shared<SolidColourBrush>(Colours::Gainsboro, true));
const SolidColourBrushSPtr Brushes::LightGray(std::make_shared<SolidColourBrush>(Colours::LightGray, true));
const SolidColourBrushSPtr Brushes::Silver(std::make_shared<SolidColourBrush>(Colours::Silver, true));
const SolidColourBrushSPtr Brushes::DarkGray(std::make_shared<SolidColourBrush>(Colours::DarkGray, true));
const SolidColourBrushSPtr Brushes::DimGray(std::make_shared<SolidColourBrush>(Colours::DimGray, true));
const SolidColourBrushSPtr Brushes::Gray(std::make_shared<SolidColourBrush>(Colours::Gray, true));
const SolidColourBrushSPtr Brushes::LightSlateGray(std::make_shared<SolidColourBrush>(Colours::LightSlateGray, true));
const SolidColourBrushSPtr Brushes::SlateGray(std::make_shared<SolidColourBrush>(Colours::SlateGray, true));
const SolidColourBrushSPtr Brushes::DarkSlateGray(std::make_shared<SolidColourBrush>(Colours::DarkSlateGray, true));
const SolidColourBrushSPtr Brushes::Black(std::make_shared<SolidColourBrush>(Colours::Black, true));

// Misc Colours
const SolidColourBrushSPtr Brushes::Transparent(std::make_shared<SolidColourBrush>(Colours::Transparent, true));

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

