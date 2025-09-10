//! @file ObjectGL/Extensions/IngrCommands.cpp
//! @brief The definition of Ingr-specific extensions to the OpenGL Command
//! set wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/IngrCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// IngrBlendFuncSeparateAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_INGR_blend_func_separate extension.
IngrBlendFuncSeparateAPI::IngrBlendFuncSeparateAPI() :
    BaseExtension("GL_INGR_blend_func_separate")
{
}

// Grant read-only access to the underlying function pointers.
const IngrBlendFuncSeparate &IngrBlendFuncSeparateAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_INGR_blend_func_separate entry points.
void IngrBlendFuncSeparateAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendFuncSeparateINGR().
void IngrBlendFuncSeparateAPI::blendFuncSeparateIngr(BlendingFactor sfactorRGB,
                                                     BlendingFactor dfactorRGB,
                                                     BlendingFactor sfactorAlpha,
                                                     BlendingFactor dfactorAlpha) const
{
    static const char *fnName = "glBlendFuncSeparateINGR";

    beforeCommand(fnName, _api.glBlendFuncSeparateINGR);
    _api.glBlendFuncSeparateINGR(toScalar(sfactorRGB), toScalar(dfactorRGB),
                                 toScalar(sfactorAlpha), toScalar(dfactorAlpha));
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

