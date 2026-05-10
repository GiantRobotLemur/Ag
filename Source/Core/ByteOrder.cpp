//! @file Core/ByteOrder.cpp
//! @brief The definition of an interface to an object which swaps bytes
//! between particular byte orders.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Binary.hpp"
#include "Ag/Core/ByteOrder.hpp"

namespace Ag {
namespace Bin {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of ByteOrder which swaps bytes.
struct SwapByteOrder : public ByteOrder
{
public:
    // Construction/Destruction
    SwapByteOrder() = default;
    virtual ~SwapByteOrder() = default;

    // Overrides
    virtual bool requiresSwap() const override { return true; }
    virtual uint16_t toHost(uint16_t bits) const { return byteSwap(bits); }
    virtual uint32_t toHost(uint32_t bits) const { return byteSwap(bits); }
    virtual uint64_t toHost(uint64_t bits) const { return byteSwap(bits); }

    virtual uint16_t toTarget(uint16_t bits) const { return byteSwap(bits); }
    virtual uint32_t toTarget(uint32_t bits) const { return byteSwap(bits); }
    virtual uint64_t toTarget(uint64_t bits) const { return byteSwap(bits); }
};

//! @brief An implementation of ByteOrder where the host and target byte order
//! are identical.
struct NoSwapByteOrder : public ByteOrder
{
public:
    // Construction/Destruction
    NoSwapByteOrder() = default;
    virtual ~NoSwapByteOrder() = default;

    // Overrides
    virtual bool requiresSwap() const override { return false; }
    virtual uint16_t toHost(uint16_t bits) const { return bits; }
    virtual uint32_t toHost(uint32_t bits) const { return bits; }
    virtual uint64_t toHost(uint64_t bits) const { return bits; }

    virtual uint16_t toTarget(uint16_t bits) const { return bits; }
    virtual uint32_t toTarget(uint32_t bits) const { return bits; }
    virtual uint64_t toTarget(uint64_t bits) const { return bits; }
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
bool isHostLittleEndian()
{
    const uint16_t myValue = 0xFF00;

    return *reinterpret_cast<const uint8_t *>(&myValue) == 0x00;
}

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const SwapByteOrder Swapping;
static const NoSwapByteOrder NoSwapping;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ByteOrder Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets an object representing a byte order expressed via a parameter.
//! @param[in] order The byte order to obtain an object for.
const ByteOrder *ByteOrder::get(Endedness order)
{
    switch (order)
    {
    case Endedness::LittleEndian:
        return getLittleEndian();

    case Endedness::BigEndian:
        return getBigEndian();

    case Endedness::Reverse:
        return &Swapping;

    case Endedness::Native:
    default:
        return &NoSwapping;
    }
}

//! @brief Gets an object to convert byte order to/from little endian encoding.
const ByteOrder *ByteOrder::getLittleEndian()
{
    return isHostLittleEndian() ? static_cast<const ByteOrder *>(&NoSwapping) :
                                  static_cast<const ByteOrder *>(&Swapping);
}

//! @brief Gets an object to convert byte order to/from big endian encoding.
const ByteOrder *ByteOrder::getBigEndian()
{
    return isHostLittleEndian() ? static_cast<const ByteOrder *>(&Swapping) :
                                  static_cast<const ByteOrder *>(&NoSwapping);
}

}} // namespace Ag::Bin
////////////////////////////////////////////////////////////////////////////////

