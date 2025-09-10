//! @file Ag/ObjectGL/Extensions/HPCommands.hpp
//! @brief The declaration of HP-specific extensions to the OpenGL Command set
//! wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_HP_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_HP_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "HP.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_HP_image_transform extension API.
class HPImageTransformAPI : public BaseExtension
{
public:
    // Construction
    HPImageTransformAPI();

    // Accessors
    const HPImageTransform &getRawAPI() const;

    // Operations
    void getImageTransformParameterFV(ImageTransformTargetHP target,
                                      ImageTransformPNameHP pname,
                                      GLfloat *params) const;
    void getImageTransformParameterIV(ImageTransformTargetHP target,
                                      ImageTransformPNameHP pname, GLint *params) const;
    void imageTransformParameterF(ImageTransformTargetHP target,
                                  ImageTransformPNameHP pname, GLfloat param) const;
    void imageTransformParameterFV(ImageTransformTargetHP target,
                                   ImageTransformPNameHP pname,
                                   const GLfloat *params) const;
    void imageTransformParameterI(ImageTransformTargetHP target,
                                  ImageTransformPNameHP pname, GLint param) const;
    void imageTransformParameterIV(ImageTransformTargetHP target,
                                   ImageTransformPNameHP pname,
                                   const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    HPImageTransform _api;
};



} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
