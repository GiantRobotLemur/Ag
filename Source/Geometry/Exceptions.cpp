//! @file Geometry/Exceptions.cpp
//! @brief The definition of various exception classes which are specific to the
//! domain of 2D geometry.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/Exceptions.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// NegativeSizeException Class Member Definitions
////////////////////////////////////////////////////////////////////////////////
const char *NegativeSizeException::Domain = "NegativeSizeException";

//! @brief Constructs an exception object defining when the program attempted
//! to process a spatial size with a negative value.
//! @param[in] isWidth True if the width component was negative or false if the
//! height component was negative.
NegativeSizeException::NegativeSizeException(bool isWidth)
{
    initialise(Domain, "The program attempted to define spatial extents with "
               "a negative component.",
               isWidth ? "The width component was negative." :
                         "The height component was negative",
               isWidth ? 1 : 2);
}

////////////////////////////////////////////////////////////////////////////////
// ZeroLengthVectorException Class Member Definitions
////////////////////////////////////////////////////////////////////////////////
const char *ZeroLengthVectorException::Domain = "ZeroLengthVectorException";

//! @brief Constructs an exception thrown when a vector which has a length of
//! near-enough zero is used in calculations where that situation is invalid.
//! @param[in] detail Details of the operation taking place when the invalid
//! vector was encountered.
ZeroLengthVectorException::ZeroLengthVectorException(utf8_cptr_t detail)
{
    initialise(Domain, "The program encountered a vector with zero length in "
               "an operation where that situation was invalid.", detail);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

