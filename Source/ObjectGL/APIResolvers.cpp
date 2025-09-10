//! @file ObjectGL/APIResolvers.cpp
//! @brief The definition of various implementations of APIResolver required
//! by the generated OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/APIResolvers.hpp"
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utils.hpp"

#ifdef _WIN32
#include "Ag/ObjectGL/WGL_API.hpp"
#endif

#ifdef _WIN32
namespace wgl {


} // namespace wgl
#endif // ifdef _WIN32

////////////////////////////////////////////////////////////////////////////////

