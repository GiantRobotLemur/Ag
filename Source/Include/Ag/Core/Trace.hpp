//! @file Ag/Core/Trace.hpp
//! @brief The declaration of
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_TRACE_HPP__
#define __AG_CORE_TRACE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Configuration.hpp"
#include "VariantTypes.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void TRACE(Ag::utf8_cptr_t text);
void TRACE(Ag::utf8_cptr_t spec, const Ag::Variant &item);
void TRACE(Ag::utf8_cptr_t spec, const Ag::Variant &item1,
           const Ag::Variant &item2);
void TRACE(Ag::utf8_cptr_t spec, const Ag::Variant &item1,
           const Ag::Variant &item2, const Ag::Variant &item3);
#else
//! @brief A macro used as a place holder for calls to a function to output
//! formatted lines of text to any listening debugger.
#define TRACE
#endif

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
void traceInternal(utf8_cptr_t spec, const VariantList &values);

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
