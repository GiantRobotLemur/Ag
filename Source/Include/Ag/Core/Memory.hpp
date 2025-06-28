//! @file Ag/Core/Memory.hpp
//! @brief The declaration of utility functions related to memory management.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_MEMORY_HPP__
#define __AG_CORE_MEMORY_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <exception>
#include <memory>
#include <new>

#ifndef __cpp_lib_hardware_interference_size
    // Make up for the lack of definitions provided with gcc.
namespace std {
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
}
#endif

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
void *mallocAligned(size_t alignment, size_t sizeInBytes);
void *mallocAlignedPow2(uint8_t alignmentPow2, size_t sizeInBytes);
void freeAligned(void *alignedBlock);

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief A type suitable for use as the deleter in an std:: unique_ptr<> type
//! declaration where the object is constructed in a region of memory allocated
//! using mallocAligned*().
//! @tparam T The data type of the object being deleted.
template<typename T> struct AlignedDeleter
{
    void operator()(T *obj) const
    {
        if (obj != nullptr)
        {
            // Manually call the destructor.
            obj->~T();

            // Free the block of memory.
            freeAligned(obj);
        }
    }
};

//! @brief A template structure used to dynamically allocate objects on fixed
//! address boundaries.
//! @tparam T The data type of the object being instantiated.
//! @tparam TAlignment The address boundary at which the object must be stored,
//! must be a power of 2.
template<typename T, size_t TAlignment = alignof(T)>
struct AlignmentTraits
{
    static constexpr size_t Alignment = TAlignment;
    using TargetType = T;
    using Deleter = AlignedDeleter<T>;
    using UPtr = std::unique_ptr<T, Deleter>;

    //! @brief Dynamically allocates an object on an aligned address boundary.
    //! @tparam TArgs The types of the construction arguments of the object
    //! to construct.
    //! @param[in] args The argument values to pass to the object constructor.
    //! @return A newly allocated object wrapped in a unique_ptr<> so that it is
    //! properly disposed of when going out of scope.
    template<typename... TArgs>
    static UPtr create(TArgs&&... args)
    {
        void *block = mallocAligned(TAlignment, sizeof(TargetType));

        return UPtr(new(block) TargetType(std::forward<TArgs>(args)...));
    }
};

//! @brief Dynamically allocates an object on an aligned address boundary.
//! @tparam T The data type of the object to allocate and construct.
//! @tparam TAlignment The address boundary at which the object must be stored,
//! must be a power of 2.
//! @tparam TArgs The types of the construction arguments of the object to construct.
//! @param[in] args The argument values to pass to the object constructor.
//! @return A newly allocated object which needs to be manually destroyed and
//! de-allocated using freeAligned(), or via AlignedDeleter<T>.
template<typename T, size_t TAlignment = alignof(T), typename... TArgs>
T *createAligned(TArgs... args)
{
    void *block = mallocAligned(TAlignment, sizeof(T));

    return new(block) T(std::forward(args)...);
}

//! @brief Dynamically allocates an object on an aligned address boundary.
//! @tparam T The data type of the object to allocate and construct.
//! @tparam TAlignment The address boundary at which the object must be stored,
//! must be a power of 2.
//! @tparam TArgs The types of the construction arguments of the object to construct.
//! @param[in] args The argument values to pass to the object constructor.
//! @return A newly allocated object wrapped in a unique_ptr<> so that it is
//! properly disposed of when going out of scope.
template<typename T, size_t TAlignment = alignof(T), typename... TArgs>
std::unique_ptr<T, AlignedDeleter<T>> createUniqueAligned(TArgs&&... args)
{
    void *block = mallocAligned(TAlignment, sizeof(T));

    return std::unique_ptr<T, AlignedDeleter<T>>(new(block) T(std::forward<TArgs>(args)...));
}

// Inspired by: https://stackoverflow.com/questions/60169819/modern-approach-to-making-stdvector-allocate-aligned-memory
//! @brief Returns aligned pointers when allocations are requested. Default alignment
//! is 64B = 512b, sufficient for AVX-512 and most cache line sizes.
//! @tparam ALIGNMENT_IN_BYTES Must be a positive power of 2.
template<typename ElementType, std::size_t ALIGNMENT_IN_BYTES = 64>
class AlignedAllocator
{
private:
    static_assert(
        ALIGNMENT_IN_BYTES >= alignof(ElementType),
        "Beware that types like int have minimum alignment requirements "
        "or access will result in crashes."
        );

public:
    using value_type = ElementType;
    static std::align_val_t constexpr ALIGNMENT{ ALIGNMENT_IN_BYTES };

    /**
     * This is only necessary because AlignedAllocator has a second template
     * argument for the alignment that will make the default
     * std::allocator_traits implementation fail during compilation.
     * @see https://stackoverflow.com/a/48062758/2191065
     */
    template<class OtherElementType> struct rebind
    {
        using other = AlignedAllocator<OtherElementType, ALIGNMENT_IN_BYTES>;
    };

public:
    constexpr AlignedAllocator() noexcept = default;

    constexpr AlignedAllocator(const AlignedAllocator &) noexcept = default;

    template<typename U>
    constexpr AlignedAllocator(AlignedAllocator<U, ALIGNMENT_IN_BYTES> const &) noexcept
    {
    }

    [[nodiscard]] ElementType *allocate(std::size_t elementCount)
    {
        if (elementCount >
            std::numeric_limits<std::size_t>::max() / sizeof(ElementType))
        {
            throw std::bad_array_new_length();
        }

        auto const bytesToAllocate = elementCount * sizeof(ElementType);
        return reinterpret_cast<ElementType *>(::operator new[](bytesToAllocate, ALIGNMENT));
    }

    void deallocate(ElementType *allocatedPointer,
                    [[maybe_unused]] std::size_t byteAllocated)
    {
        /* According to the C++20 draft n4868 § 17.6.3.3, the delete operator
         * must be called with the same alignment argument as the new expression.
         * The size argument can be omitted but if present must also be equal to
         * the one used in new. */
        ::operator delete[](allocatedPointer, ALIGNMENT);
    }
};

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
