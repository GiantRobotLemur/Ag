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
#include <cstdint>
#include <bit>

namespace Ag {
namespace Bin {

////////////////////////////////////////////////////////////////////////////////
// Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An enumeration type describing byte order.
enum class Endedness : uint8_t
{
    //! @brief The least significant byte is stored at the lowest address.
    LittleEndian,

    //! @brief The most significant byte is stored at the lowest address.
    BigEndian,

    //! @brief The byte order matches that of the host hardware.
    Native,

    //! @brief The byte order which is the reverse of the host hardware.
    Reverse,
};

//! @brief Provides a concrete value for the host byte order.
constexpr Endedness HostByteOrder =
    (std::endian::native == std::endian::little) ? Endedness::LittleEndian :
                                                   Endedness::BigEndian;

//! @brief Provides a concrete value for the byte ordering opposed to the
//! host order.
constexpr Endedness ReverseByteOrder =
    (std::endian::native == std::endian::little) ? Endedness::BigEndian :
                                                   Endedness::LittleEndian;

//! @brief A template structure which determines if a byte swap is needed
//! to encode data in a specified byte order.
//! @tparam TargetByteOrder The byte order to encode data as.
template<Endedness TargetByteOrder>
struct NeedsSwap
{
    static constexpr bool value = (HostByteOrder != TargetByteOrder);
};

//! @brief A template structure which resolves the byte order based on whether
//! a byte swap has been implemented at compile type
//! @tparam IsSwapped True if bytes are swapped, false if in host order.
template<bool IsSwapped>
struct ResolvedByteOrder
{
    static constexpr Endedness value = IsSwapped ? ReverseByteOrder : HostByteOrder;
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Implements functions which swap bytes between a particular
//! byte order and the host byte order.
struct ByteOrder
{
protected:
    // Construction/Destruction
    ByteOrder() = default;
    virtual ~ByteOrder() = default;

public:
    // Accessors
    static const ByteOrder *get(Endedness order);
    static const ByteOrder *getLittleEndian();
    static const ByteOrder *getBigEndian();

    // Operations
    //! @brief Determines whether bytes need to be swapped to convert from
    //! native byte order to the described byte order.
    //! @retval true The order of bytes needs to be reversed to convert.
    //! @retval false The byte order represents that of the host architecture.
    virtual bool requiresSwap() const = 0;

    //! @brief Converts a 16-bit word from the described byte order to the
    //! native encoding of the host architecture.
    //! @param[in] bits The word encoded in the described byte order.
    //! @return The word encoded in the host byte order.
    virtual uint16_t toHost(uint16_t bits) const = 0;

    //! @brief Converts a 32-bit word from the described byte order to the
    //! native encoding of the host architecture.
    //! @param[in] bits The word encoded in the described byte order.
    //! @return The word encoded in the host byte order.
    virtual uint32_t toHost(uint32_t bits) const = 0;

    //! @brief Converts a 64-bit word from the described byte order to the
    //! native encoding of the host architecture.
    //! @param[in] bits The word encoded in the described byte order.
    //! @return The word encoded in the host byte order.
    virtual uint64_t toHost(uint64_t bits) const = 0;

    //! @brief Converts a 16-bit word from the host byte order to the byte order
    //! described by the current object.
    //! @param[in] bits The word encoded in host byte order to convert.
    //! @return The word in the described byte order.
    virtual uint16_t toTarget(uint16_t bits) const = 0;

    //! @brief Converts a 32-bit word from the host byte order to the byte order
    //! described by the current object.
    //! @param[in] bits The word encoded in host byte order to convert.
    //! @return The word in the described byte order.
    virtual uint32_t toTarget(uint32_t bits) const = 0;

    //! @brief Converts a 64-bit word from the host byte order to the byte order
    //! described by the current object.
    //! @param[in] bits The word encoded in host byte order to convert.
    //! @return The word in the described byte order.
    virtual uint64_t toTarget(uint64_t bits) const = 0;
};

}} // namespace Ag::Bin

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
