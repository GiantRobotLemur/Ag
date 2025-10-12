//! @file Ag/Core/AlignedTypes.hpp
//! @brief The declaration of compile-time utilities for creating classes and
//! structures which are properly aligned on specific address boundaries.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_ALIGNED_TYPES_HPP__
#define __AG_CORE_ALIGNED_TYPES_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <type_traits>

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A utility base class to be used if a shared_ptr-compatible object
//! needs to implement virtual functions.
//! @remarks This data type can be used as an input to the various data type
//! alignment compile-time functions.
class SharedVirtualBase : public std::enable_shared_from_this<SharedVirtualBase>
{
public:
    SharedVirtualBase() = default;
    virtual ~SharedVirtualBase() = default;
};

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief A compile-time function which calculates whether the size of a
//! data type has a size which allows consecutive instances to be contiguous
//! in memory without padding.
//! @tparam T The data type to test.
//! @tparam N The number of bytes the type size must be an even multiple of to
//! require no padding.
template<typename T, size_t N> struct IsSizeAlignedN
{
    //! @brief True if T has a size which is an exact multiple if N, else false.
    static constexpr bool value = ((sizeof(T) % N) == 0);
};

//! @brief A compile-time function which calculates whether the size of a
//! data type has a size which allows consecutive instances to be contiguous
//! in memory without padding.
//! @tparam T The data type to test.
//! @tparam N The data type with an alignment which defines the address boundary
//! on which the size of T must be aligned.
template<typename T, typename U> struct IsSizeAligned :
    public IsSizeAlignedN<T, alignof(U)> {
};

//! @brief A compile-time function which rounds the size of a data type up to
//! the next multiple of a specified size.
//! @tparam T The data type defining the base size.
//! @tparam N The multiple to round up to, adding at most N bytes to the size
//! of T.
template<typename T, size_t N> struct RoundedUpSizeN
{
    static constexpr size_t value = ((sizeof(T) / N) + 1) * N;
};

//! @brief A compile-time function which rounds the size of a data type up to
//! the next multiple of the alignment requirements of another type.
//! @tparam T The data type defining the base size.
//! @tparam U The data type with an alignment defining the multiple to round
//! up to, adding at most alignof(U) bytes to the size of T.
template<typename T, typename U> struct RoundedUpSize :
    public RoundedUpSizeN<T, alignof(U)> {
};

//! @brief A compile-time type switch which selects a data structure or a padded
//! version of it.
//! @tparam T The data type of the data structure to optionally pad.
//! @tparam N The count of bytes to pad the data structure to an even multiplier of.
template<typename T, size_t N> struct AlignedBaseN
{
    //! @brief A padded version of the data structure T with a constructor
    //! which zeros the padding bytes.
    struct PaddedBase : public T
    {
    private:
        // Pad with up to alignof(U) bytes to align the base class.
        uint8_t Padding[RoundedUpSizeN<T, N>::value];
    public:
        PaddedBase()
        {
            std::fill_n(Padding, std::size(Padding), static_cast<uint8_t>(0));
        }
    };

    //! @brief A type which selects either the padded or unpadded version of
    //! the data structure T depending on whether it needs padding.
    using type = std::conditional_t<IsSizeAlignedN<T, N>::value, T, PaddedBase>;
};

//! @brief An alias for a possibly padded data type.
//! @tparam T The base type to possibly be padded.
//! @tparam N The count of bytes to pad the data type, T, to fit.
template<typename T, size_t N> using AlignedBaseN_t = typename AlignedBaseN<T, N>::type;

//! @brief Defines a structure type which had a size which aligns to the
//! address boundary of a specified data type.
//! @tparam T The data type to align.
//! @tparam U The data type providing the alignment constraints.
template<typename T, typename U> struct AlignedBase : public AlignedBaseN<T, alignof(U) > {};

//! @brief An alias for a base class which may or may not have padding applied.
//! @tparam T The data type to pad.
//! @tparam U The data type providing the alignment constraints.
template<typename T, typename U> using AlignedBase_t = typename AlignedBase<T, U>::type;

//! @brief Defines a data type selected according to whether its size is a whole
//! multiple of its address alignment constraint.
//! @tparam TBase The un-padded version of the data type returned if the data
//! type is already properly aligned.
//! @tparam TPadded The padded version of the data type returned if padding
//! is required.
template<typename TBase, typename TPadded> struct AlignedType
{
    using type = std::conditional_t<IsSizeAligned<TBase, TBase>::value,
        TBase, TPadded>;
};

//! @brief An alias for a data type which could be padded to a size with
//! fits alignment constraints of another type.
//! @tparam TBase The data type to pad.
//! @tparam TPadded The data type providing the padding size alignment constraint.
template<typename TBase, typename TPadded> using AlignedType_t = typename AlignedType<TBase, TPadded>::type;

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
