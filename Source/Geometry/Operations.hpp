//! @file Geometry/Operations.hpp
//! @brief A header which determines which set of SIMD-accelerated operations
//! to use internally within the library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_OPERATIONS_HPP__
#define __AG_GEOMETRY_OPERATIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#if defined(AG_ENABLE_X64_V4) || defined(AG_ENABLE_X64_V3) || defined(AG_ENABLE_X64_V2)
#include "Operations_x64v2.hpp"
#elif defined(AG_ENABLE_X64_V1)
#include "Operations_x64v1.hpp"
#else
#include "Operations_Base.hpp"
#endif

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
namespace Ag {
namespace Geom {

// TODO: Implement SSE2/4/AVX acceleration for 3x3 matrices.
using Operations_Mat3x3D = OperationsBase_Mat3x3D;

#if defined(AG_ENABLE_X64_V4) || defined(AG_ENABLE_X64_V3) || defined(AG_ENABLE_X64_V2)
using Operations_Vec2D = OperationsX64v2_Vec2D;
using Operations_Mat2x2D = OperationsX64v2_Mat2x2D;
using Operations_AffineTrans2D = OperationsX64v2_AffineTrans2D;
#elif defined(AG_ENABLE_X64_V1)
using Operations_Vec2D = OperationsX64v1_Vec2D;
using Operations_Mat2x2D = OperationsX64v1_Mat2x2D;
using Operations_AffineTrans2D = OperationsX64v1_AffineTrans2D;
#else
using Operations_Vec2D = OperationsBase_Vec2D;
using Operations_Mat2x2D = OperationsBase_Mat2x2D;
using Operations_AffineTrans2D = OperationsBase_AffineTrans2D;
#endif

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
