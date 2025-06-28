//! @file Geometry/Exceptions.hpp
//! @brief The declaration of various exception classes which are specific to the
//! domain of 2D geometry.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_EXCEPTIONS_HPP__
#define __AG_GEOMETRY_EXCEPTIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <Ag/Core/Exception.hpp>

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An exception thrown when an attempt is made to set a size component
//! to a negative value.
class NegativeSizeException : public Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static const char *Domain;

    // Construction/Destruction
    NegativeSizeException(bool isWidth);
};

//! @brief An exception thrown when a vector which has a length of near-enough
//! zero is used in calculations where that situation is invalid.
class ZeroLengthVectorException : public Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static const char *Domain;

    // Construction/Destruction
    ZeroLengthVectorException(utf8_cptr_t detail);
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
