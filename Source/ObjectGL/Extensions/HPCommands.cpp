//! @file ObjectGL/Extensions/HPCommands.cpp
//! @brief The definition of HP-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/HPCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// HPImageTransformAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_HP_image_transform extension.
HPImageTransformAPI::HPImageTransformAPI() :
    BaseExtension("GL_HP_image_transform")
{
}

// Grant read-only access to the underlying function pointers.
const HPImageTransform &HPImageTransformAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_HP_image_transform entry points.
void HPImageTransformAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetImageTransformParameterfvHP().
void HPImageTransformAPI::getImageTransformParameterFV(ImageTransformTargetHP target,
                                                       ImageTransformPNameHP pname,
                                                       GLfloat *params) const
{
    static const char *fnName = "glGetImageTransformParameterfvHP";

    beforeCommand(fnName, _api.glGetImageTransformParameterfv);
    _api.glGetImageTransformParameterfv(toScalar(target), toScalar(pname),
                                        params);
    afterCommand(fnName);
}

// Calls glGetImageTransformParameterivHP().
void HPImageTransformAPI::getImageTransformParameterIV(ImageTransformTargetHP target,
                                                       ImageTransformPNameHP pname,
                                                       GLint *params) const
{
    static const char *fnName = "glGetImageTransformParameterivHP";

    beforeCommand(fnName, _api.glGetImageTransformParameteriv);
    _api.glGetImageTransformParameteriv(toScalar(target), toScalar(pname),
                                        params);
    afterCommand(fnName);
}

// Calls glImageTransformParameterfHP().
void HPImageTransformAPI::imageTransformParameterF(ImageTransformTargetHP target,
                                                   ImageTransformPNameHP pname,
                                                   GLfloat param) const
{
    static const char *fnName = "glImageTransformParameterfHP";

    beforeCommand(fnName, _api.glImageTransformParameterf);
    _api.glImageTransformParameterf(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glImageTransformParameterfvHP().
void HPImageTransformAPI::imageTransformParameterFV(ImageTransformTargetHP target,
                                                    ImageTransformPNameHP pname,
                                                    const GLfloat *params) const
{
    static const char *fnName = "glImageTransformParameterfvHP";

    beforeCommand(fnName, _api.glImageTransformParameterfv);
    _api.glImageTransformParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glImageTransformParameteriHP().
void HPImageTransformAPI::imageTransformParameterI(ImageTransformTargetHP target,
                                                   ImageTransformPNameHP pname,
                                                   GLint param) const
{
    static const char *fnName = "glImageTransformParameteriHP";

    beforeCommand(fnName, _api.glImageTransformParameteri);
    _api.glImageTransformParameteri(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glImageTransformParameterivHP().
void HPImageTransformAPI::imageTransformParameterIV(ImageTransformTargetHP target,
                                                    ImageTransformPNameHP pname,
                                                    const GLint *params) const
{
    static const char *fnName = "glImageTransformParameterivHP";

    beforeCommand(fnName, _api.glImageTransformParameteriv);
    _api.glImageTransformParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

