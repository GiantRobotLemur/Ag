//! @file Ag/Sdl3Tools/ApiException.hpp
//! @brief The declaration of an exception documenting the unexpected failure
//! of an SDL function.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_API_EXCEPTION_HPP__
#define __AG_SDL3_TOOLS_API_EXCEPTION_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Variant.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An exception documenting the unexpected failure of an SDL function.
class ApiException : public Ag::Exception
{
public:
    // Public Fields
    static const char *Domain;

    // Construction/Destruction
    ApiException(const char *fnName);
    ApiException(const char *fnName, string_cref_t detail);
    ApiException(const char *fnNameFormat, const Ag::VariantList &args);
    ~ApiException() = default;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
