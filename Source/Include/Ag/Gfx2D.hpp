//! @file Ag/Gfx2D.hpp
//! @brief The declaration of the root header file for the Gfx2D library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_HPP__
#define __GFX_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Core.hpp"
#include "Geometry.hpp"

#ifdef AG_OBJECT_GL
// ObjectGL can be linked.
#include "ObjectGL.hpp"
#endif // ifdef AG_OBJECT_GL

#ifdef AG_SDL3_TOOLS
#include "Sdl3Tools.hpp"
#endif // ifdef AG_SDL3_TOOLS

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Gfx2D/Colour.hpp"
#include "Gfx2D/Colours.hpp"
#include "Gfx2D/Brush.hpp"
#include "Gfx2D/Brushes.hpp"
#include "Gfx2D/Pen.hpp"
#include "Gfx2D/Font.hpp"
#include "Gfx2D/Path.hpp"
#include "Gfx2D/Graphic.hpp"

#include "Gfx2D/GraphicArtefact.hpp"
#include "Gfx2D/PartitionedPolygon.hpp"
#include "Gfx2D/GraphicDecomposition.hpp"
#include "Gfx2D/GraphicGroup.hpp"
#include "Gfx2D/Scene.hpp"
#include "Gfx2D/PrimitiveGraphics.hpp"


#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
