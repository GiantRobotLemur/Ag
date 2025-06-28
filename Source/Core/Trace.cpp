//! @file Core/Trace.cpp
//! @brief The definition of functions which output text to an attached debugger.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "Ag/Core/Trace.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Core/Platform.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Formats a line of text and sends it to any listening debugger.
//! @param[in] spec The Ag::String::Format()-style format specification text.
//! @param[in] values The collection of values to be formatted as text.
void traceInternal(utf8_cptr_t spec, const VariantList &values)
{
    auto text = String::format(spec, values);

#ifdef WIN32
    std::wstring wideText = text.toWide();
    wideText.push_back(L'\n');

    ::OutputDebugStringW(wideText.c_str());
#else
    // As std::string_view is bounded, write a bounded string to the error output.
    auto view = text.toUtf8View();
    fwrite(view.data(), sizeof(char), view.size(), stderr);
#endif
}

} // namespace Ag

#ifdef _DEBUG
//! @brief A function/macro for outputting a line of text to any listening
//! debugger.
//! @param[in] text The UTF-8 encoded text to send.
void TRACE(Ag::utf8_cptr_t text)
{
#ifdef WIN32
    std::wstring buffer;
    Ag::Utf::appendToWide(buffer, text, strlen(text));
    buffer.push_back(L'\n');

    ::OutputDebugStringW(buffer.c_str());
#else
    // Use fwrite() for non-formatted output for consistency.
    fwrite(text, sizeof(char), strlen(text), stderr);
#endif
}

//! @brief Formats a line of text and sends it to any listening debugger.
//! @param[in] spec The Ag::String::Format()-style format specification text.
//! @param[in] item The single data item to be formatted into the output text.
void TRACE(Ag::utf8_cptr_t spec, const Ag::Variant &item)
{
    Ag::traceInternal(spec, { item });
}

//! @brief Formats a line of text and sends it to any listening debugger.
//! @param[in] spec The Ag::String::Format()-style format specification text.
//! @param[in] item1 The first data item to be formatted into the output text.
void TRACE(Ag::utf8_cptr_t spec, const Ag::Variant &item1, const Ag::Variant &item2)
{
    Ag::traceInternal(spec, { item1, item2 });
}

//! @brief Formats a line of text and sends it to any listening debugger.
//! @param[in] spec The Ag::String::Format()-style format specification text.
//! @param[in] item1 The first data item to be formatted into the output text.
//! @param[in] item2 The second data item to be formatted into the output text.
//! @param[in] item3 The third data item to be formatted into the output text.
void TRACE(Ag::utf8_cptr_t spec, const Ag::Variant &item1,
           const Ag::Variant &item2, const Ag::Variant &item3)
{
    Ag::traceInternal(spec, { item1, item2, item3 });
}

#endif
////////////////////////////////////////////////////////////////////////////////

