//! @file Ag/Core/Binary.hpp
//! @brief The declaration of various stand-alone operations on binary values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2023
//! @copyright This file is part of the Mighty Oak project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/MightyOak for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_BINARY_HPP__
#define __AG_CORE_BINARY_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <atomic>
#include <type_traits>
#include <vector>

#include "Configuration.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
using ByteBlock = std::vector<uint8_t>;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
namespace Bin {
bool bitScanForward(uint32_t value, int32_t &msb);
bool bitScanForward(uint64_t value, int32_t &msb);
bool bitScanReverse(uint32_t value, int32_t &msb);
bool bitScanReverse(uint64_t value, int32_t &msb);
int32_t log2(uint32_t value, bool roundUp);
int32_t log2(uint64_t value, bool roundUp);
uint32_t rotateLeft(uint32_t bits, int32_t shift);
uint64_t rotateLeft(uint64_t bits, int32_t shift);
uint32_t rotateRight(uint32_t bits, int32_t shift);
uint64_t rotateRight(uint64_t bits, int32_t shift);

uint16_t byteSwap(uint16_t bits);
uint32_t byteSwap(uint32_t bits);
uint64_t byteSwap(uint64_t bits);

uint8_t popCount(uint16_t bits);
uint8_t popCount(uint32_t bits);

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief Makes a mask of a specified number of consecutive set bits.
//! @tparam TIntegral The unsigned integer type of the mask to create.
//! @param[in] bitCount The count of consecutive bits to set.
//! @return A mask of bits in the appropriate integral type.
template<typename TIntegral> constexpr TIntegral makeMask(int32_t bitCount)
{
    TIntegral mask = 0;

    if (bitCount > 0)
    {
        mask = (static_cast<TIntegral>(1) << bitCount) - static_cast<TIntegral>(1);
    }

    return mask;
}

//! @brief Rounds an unsigned integral value up to the nearest whole multiple
//! of a specified power of 2.
//! @tparam TIntegral The unsigned integer type of the value to round up.
//! @param[in] value The value to round up.
//! @param[in] pow2 The power of 2 to round up to.
//! @return The rounded up value, possibly equal to the input value if value was
//! already a whole multiple of the specified power of 2.
template<typename TIntegral> TIntegral roundUpPow2(TIntegral value, int32_t pow2)
{
    if (pow2 > 0)
    {
        TIntegral mask = makeMask<TIntegral>(pow2);

        value = (value + mask) & ~mask;
    }

    return value;
}

//! @brief Extracts a bit from a bitfield.
//! @tparam TBit The 0-based index of the bit to extract.
//! @tparam TField The data type of the bitfield be queried.
//! @param[in] bitfield The bit field to extract the bit from.
//! @returns Either 0 or 1 depending on the bit state.
template<uint8_t TBit, typename TField>
constexpr uint8_t extractBit(TField bitfield) noexcept
{
    constexpr uint8_t FieldBits = sizeof(TField) * 8;
    static_assert(TBit < FieldBits, "TBit out of range in extractBit<TBit>().");

    if constexpr (TBit == (FieldBits - 1))
    {
        // No need to mask, save ourselves an AND instruction.
        return static_cast<uint8_t>(bitfield >> TBit);
    }
    else
    {
        return static_cast<uint8_t>(bitfield >> TBit) & 1;
    }
}

// Tests for extratBit<>().
// Verify shift and mask.
static_assert(extractBit<12, uint32_t>(0) == 0, "extractBit() failed.");
static_assert(extractBit<12, uint32_t>(0x1000) == 1, "extractBit() failed.");

// Verify just shift.
static_assert(extractBit<31, uint32_t>(0) == 0, "extractBit() failed.");
static_assert(extractBit<31, uint32_t>(0x80000000) == 1, "extractBit() failed.");

//! @brief Extracts a scalar value from a bitfield.
//! @tparam TOutput The data type of the scalar value being extracted.
//! @tparam TInput The data type of the input value to extract from.
//! @tparam TLsb The 0-based index of the least significant bit of the value
//! to extract.
//! @tparam TCount The count of consecutive bits to extract.
//! @param bitfield The bitfield to extract bits from.
//! @return The extracted bits as the required enumeration type.
template<typename TOutput, uint8_t TLsb, uint8_t TCount, typename TInput>
constexpr TOutput extractBits(TInput bitfield) noexcept
{
    constexpr uint8_t InputBits = sizeof(TInput) * 8;
    static_assert((TLsb + TCount) <= InputBits,
                  "The bits to extract are beyond the range of the input field.");

    if constexpr (InputBits == (TLsb + TCount))
    {
        // No need to mask, save ourselves an AND instruction.
        return static_cast<TOutput>(bitfield >> TLsb);
    }
    else
    {
        constexpr TOutput Mask = (static_cast<TOutput>(1) << TCount) - 1;

        return static_cast<TOutput>(bitfield >> TLsb) & Mask;
    }
}

// Tests for extarctBits<>();
// Verify shift and mask.
static_assert(extractBits<uint8_t, 12, 4, uint32_t>(0) == 0, "extractBits() failed.");
static_assert(extractBits<uint8_t, 12, 4, uint32_t>(0x5ABCD) == 10, "extractBits() failed.");

// Verify just shift.
static_assert(extractBits<uint8_t, 28, 4, uint32_t>(0x60000000) == 6, "extractBits() failed.");
static_assert(extractBits<uint8_t, 24, 8, uint32_t>(0xDEADBEEF) == 0xDE, "extractBits() failed.");

//! @brief Extracts a scalar value from a bitfield.
//! @tparam TOutput The data type of the scalar value being extracted.
//! @tparam TInput The data type of the input value to extract from.
//! @tparam TLsb The 0-based index of the least significant bit of the value
//! to extract.
//! @tparam TNewLsb The 0-based index of the least significant bit of the
//! value as it is shifted into the new field.
//! @tparam TCount The count of consecutive bits to extract.
//! @param bitfield The bitfield to extract bits from.
//! @return The extracted bits as the required enumeration type.
template<typename TOutput, uint8_t TLsb, uint8_t TNewLsb, uint8_t TCount, typename TInput>
constexpr TOutput extractAndShiftBits(TInput bitfield) noexcept
{
    constexpr uint8_t InputBits = sizeof(TInput) * 8;
    static_assert((TLsb + TCount) <= InputBits,
                  "The bits to extract are beyond the range of the input field.");

    constexpr uint8_t OutputBits = sizeof(TOutput) * 8;
    static_assert((TNewLsb + TCount) <= OutputBits,
                  "The bits to set are beyond the range of the output field.");

    constexpr int TotalShift = static_cast<int>(TNewLsb) - static_cast<int>(TLsb);

    if constexpr (TotalShift < 0)
    {
        // We need to shift the result right.
        constexpr uint8_t RightShift = TLsb - TNewLsb;
        constexpr TOutput OutputMask = ((static_cast<TOutput>(1) << TCount) - 1) << TNewLsb;

        return static_cast<TOutput>(bitfield >> RightShift) & OutputMask;
    }
    else if constexpr (TotalShift > 0)
    {
        // We need to shift left.
        constexpr uint8_t LeftShift = TNewLsb - TLsb;
        constexpr TInput InputMask = ((static_cast<TInput>(1) << TCount) - 1) << TLsb;

        return static_cast<TOutput>(bitfield & InputMask) << LeftShift;
    }
    else if constexpr (sizeof(TOutput) < sizeof(TInput))
    {
        // We don't need to shift, but the mask would be a smaller
        // field in the output type.
        constexpr TOutput OutputMask = ((static_cast<TOutput>(1) << TCount) - 1) << TLsb;

        return static_cast<TOutput>(bitfield) & OutputMask;
    }
    else
    {
        // We don't need to shift, but the mask would be a smaller
        // field in the input type.
        constexpr TInput InputMask = ((static_cast<TInput>(1) << TCount) - 1) << TLsb;

        return static_cast<TOutput>(bitfield & InputMask);
    }
}

// Verify left shift.
static_assert(extractAndShiftBits<uint16_t, 2, 4, 6, uint8_t>(0xAD) == 0x2B0);

// Verify right shift.
static_assert(extractAndShiftBits<uint8_t, 4, 2, 6, uint16_t>(0xCAFE) == 0xBC);


//! @brief Extracts an enumeration value from a bitfield.
//! @tparam TEnum The data type of the enumeration being extracted.
//! @tparam TInput The data type of the input value to extract from.
//! @tparam TLsb The 0-based index of the least significant bit of the value
//! to extract.
//! @tparam TCount The count of consecutive bits to extract.
//! @param bitfield The bitfield to extract bits from.
//! @return The extracted bits as the required enumeration type.
template<typename TEnum, uint8_t TLsb, uint8_t TCount, typename TInput>
constexpr TEnum extractEnum(TInput bitfield) noexcept
{
    using Raw = std::underlying_type_t<TEnum>;
    constexpr uint8_t RawBits = sizeof(Raw) * 8;
    constexpr uint8_t InputBits = sizeof(TInput) * 8;
    constexpr uint8_t LastBit = TLsb + TCount;

    static_assert(TCount <= RawBits, "Too many bits requested from extractEnum<>().");
    static_assert(LastBit <= InputBits,
                  "The range of bits to extract is beyond the end of the input field.");

    if constexpr (LastBit == InputBits)
    {
        // No need to mask, save ourselves an AND instruction.
        return static_cast<TEnum>(static_cast<Raw>(bitfield >> TLsb));
    }
    else
    {
        constexpr Raw Mask = (static_cast<Raw>(1) << TCount) - 1;

        return static_cast<TEnum>(static_cast<Raw>(bitfield >> TLsb) & Mask);
    }
}

//// Verify shift and mask.
//static_assert(extractEnum<GeneralRegister, 12, 4, uint32_t>(0) == GeneralRegister::R0,
//              "extractEnum() failed.");
//static_assert(extractEnum<GeneralRegister, 12, 4, uint32_t>(0x5ABCD) == GeneralRegister::R10,
//              "extractBits() failed.");
//
//// Verify just shift.
//static_assert(extractEnum<GeneralRegister, 12, 4, uint16_t>(0x6000) == GeneralRegister::R6,
//              "extractBits() failed.");
//static_assert(extractEnum<GeneralRegister, 8, 8, uint16_t>(0x0EEF) == GeneralRegister::R14,
//              "extractBits() failed.");

//! @brief Turns a bool of true into ~0 and false to 0 using branchless code.
//! @tparam T The data type of the resultant value.
//! @param[in] flag The boolean flag to convert.
//! @return A value of (T)-1 or (T)0.
template<typename T>
constexpr T makeNegativeBool(bool flag)
{
    using SignedT = typename std::make_signed<T>::type;
    SignedT signedValue = -static_cast<int8_t>(flag);

    return static_cast<T>(signedValue);
}

//! @brief Updates a bit within a bitfield based on a boolean value.
//! @tparam T The data type of the bitfield being updated.
//! @param[in] inputMask The current state of the bitfield.
//! @param[in] bit The 0-based index of the bit to modify.
//! @param[in] state The new state of the bit.
//! @return The new mask value.
//! @note Branchless implementation.
template<typename T>
constexpr void updateBit(std::atomic<T> &inputMask, uint8_t bit, bool state) noexcept
{
    const T modifyMask = static_cast<T>(1) << bit;

    inputMask = (inputMask & ~modifyMask) | (makeNegativeBool<T>(state) & modifyMask);
}

//! @brief Updates a bit within a bitfield based on a boolean value.
//! @tparam T The data type of the bitfield being updated.
//! @param[in] inputMask The current state of the bitfield.
//! @param[in] bit The 0-based index of the bit to modify.
//! @param[in] state The new state of the bit.
//! @return The new mask value.
//! @note Branchless implementation.
template<typename T>
constexpr void updateBit(T &inputMask, uint8_t bit, bool state) noexcept
{
    const T modifyMask = static_cast<T>(1) << bit;

    inputMask = (inputMask & ~modifyMask) | (makeNegativeBool<T>(state) & modifyMask);
}

//! @brief Updates a set of bits within a bitfield based on a boolean value.
//! @tparam T The data type of the bitfield being updated.
//! @param[in] inputMask The current state of the bitfield.
//! @param[in] bitMask The mask of bits to modify.
//! @param[in] state The new state of the bit.
//! @return The new mask value.
//! @note Branchless implementation.
template<typename T>
constexpr void updateMask(T &inputMask, T bitMask, bool state) noexcept
{
    inputMask = (inputMask & ~bitMask) | (makeNegativeBool<T>(state) & bitMask);
}

} // namespace Bin
} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
