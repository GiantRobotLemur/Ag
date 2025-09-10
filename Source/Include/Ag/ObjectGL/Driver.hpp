//! @file Ag/ObjectGL/Driver.hpp
//! @brief The declaration of the interface to an object which abstracts the
//! differences between different platforms underlying OpenGL implementations.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_DRIVER_HPP__
#define __AG_OBJECT_GL_DRIVER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/BaseTypes.hpp"
#include "Ag/ObjectGL/DisplayContext.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class DisplayFormat;

//! @brief The interface to a stateless factory object which abstracts the
//! differences between different platforms underlying OpenGL implementations
//! to allow the creation of OpenGL contexts.
class IDriver
{
public:
    // Construction/Destruction
    virtual ~IDriver() = default;

    // Operations
    virtual DisplayContext createDisplayDevice(const DisplayFormat &format) const = 0;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
