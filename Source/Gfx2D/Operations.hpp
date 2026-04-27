//! @file Gfx2D/Operations.hpp
//! @brief A header which selects the appropriate Operations_*.hpp based on the
//! expected hardware.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_OPERATIONS_HPP__
#define __GFX_2D_OPERATIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#if defined(AG_ENABLE_X64_V4) || defined(AG_ENABLE_X64_V3) || defined(AG_ENABLE_X64_V2) || defined(AG_ENABLE_X64_V1)
#include "Operations_x64v1.hpp"
#else
#include "Operations_Base.hpp"
#endif

namespace Ag {

//! @brief The namespace containing elements of the Gfx2D library.
namespace Gfx2D {

#if defined(AG_ENABLE_X64_V4) || defined(AG_ENABLE_X64_V3) || defined(AG_ENABLE_X64_V2) || defined(AG_ENABLE_X64_V1)
using Operations_Vec4F = OperationsX64v1_Vec4F;
#else
using Operations_Vec4F = OperationsBase_Vec4F;
#endif

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
