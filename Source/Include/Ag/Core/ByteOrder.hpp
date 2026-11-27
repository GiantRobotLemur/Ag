//! @file Ag/Core/ByteOrder.hpp
//! @brief The declaration of an interface to an object which swaps bytes
//! between particular byte orders.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_CORE_BYTE_ORDER_HPP_
#define HEADER_AG_CORE_BYTE_ORDER_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <bit>

namespace Ag {
namespace Bin {

////////////////////////////////////////////////////////////////////////////////
// Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief Provides a concrete value for the byte ordering opposed to the
//! host order.
constexpr  std::endian ReverseByteOrder =
    (std::endian::native == std::endian::little) ? std::endian::big :
                                                   std::endian::little;

//! @brief A template structure which determines if a byte swap is needed
//! to encode data in a specified byte order.
//! @tparam TargetByteOrder The byte order to encode data as.
template<std::endian TargetByteOrder>
struct NeedsSwap
{
    static constexpr bool value = ((std::endian::native == TargetByteOrder) == false);
};

//! @brief A template structure which resolves the byte order based on whether
//! a byte swap has been implemented at compile type
//! @tparam IsSwapped True if bytes are swapped, false if in host order.
template<bool IsSwapped>
struct ResolvedByteOrder
{
    static constexpr std::endian value = IsSwapped ? ReverseByteOrder : std::endian::native;
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A compile time object which allows byte order to be swapped if necessary
//! @tparam TEndedness The byte order to be enforced, either std::endian::little or
//! std::endian::big.
template<std::endian TEndedness>
struct ByteSwapper
{
    ByteSwapper() = delete;
    ~ByteSwapper() = delete;

    // Public Constants

    //! @brief A constant giving the byte order the object was intended to encode.
    static constexpr std::endian TargetByteOrder = TEndedness;

    //! @brief A constant replicating the host byte order.
    static constexpr std::endian HostByteOrder = std::endian::native;

    //! @brief Determines whether bytes in host order need to be swapped to
    //! enforce the target byte order.
    static constexpr bool SwapToTarget = (TEndedness != std::endian::native);

    //! @brief Swaps byte order, if necessary, to convert between target and
    //! host byte order.
    //! @tparam T The data type of the value to byte swap.
    //! @param[in] value The value to be converted to/from target byte order.
    //! @return The value in the new byte order, if a swap was required.
    template<typename T> static constexpr T apply(T value)
    {
        if constexpr (SwapToTarget)
            return std::byteswap(value);
        else
            return value;
    }
};

}} // namespace Ag::Bin

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
