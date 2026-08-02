//! @file ObjectGL/CommandSetTools.hpp
//! @brief The declaration of a set of private tools used by OpenGL command
//! set wrapper implementations.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_OBJECT_GL_COMMAND_SET_TOOLS_HPP_
#define HEADER_AG_OBJECT_GL_COMMAND_SET_TOOLS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief Converts an enum class type to original type.
//! @tparam T The enumeration class type.
//! @param[in] value The enumeration value to convert to something more primitive.
//! @returns The same value as an underlying scalar type.
template<typename T, typename ScalarType = typename std::underlying_type<T>::type>
ScalarType toScalar(T value)
{
    return static_cast<ScalarType>(value);
}

//! @brief Converts a pointer to an enum class type to a pointer to its
//! underlying type.
//! @tparam T The enumeration class type.
//! @param[in] value The enumeration pointer to convert to something more primitive.
//! @returns The same value as a pointer to an underlying scalar type.
template<typename T, typename ScalarType = typename std::underlying_type<T>::type>
ScalarType *toScalarPtr(T *value)
{
    return reinterpret_cast<ScalarType *>(value);
}

//! @brief Converts a read-only pointer to an enum class type to a pointer
//! to its underlying type.
//! @tparam T The enumeration class type.
//! @param[in] value The enumeration pointer to convert to something more primitive.
//! @returns The same value as a read-only pointer to an underlying scalar type.
template<typename T, typename ScalarType = typename std::underlying_type<T>::type>
const ScalarType *toScalarPtr(const T *value)
{
    return reinterpret_cast<const ScalarType *>(value);
}

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
