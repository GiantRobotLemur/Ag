//! @file Ag/Core/Memory.hpp
//! @brief The declaration of utility functions related to memory management.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_CORE_MEMORY_HPP_
#define HEADER_AG_CORE_MEMORY_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <exception>
#include <memory>
#include <new>
#include <vector>
#include <string>
#include <string_view>

#include "Exception.hpp"

#ifndef __cpp_lib_hardware_interference_size
    // Make up for the lack of definitions provided with gcc.
namespace std {
    // 64 bytes on x86-64 │ L1_CACHE_BYTES │ L1_CACHE_SHIFT │ __cacheline_aligned │ ...
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
}
#endif

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Declares a unique pointer type with its own deleter.
//! @param[in] name The name of the type which needs a unique pointer, which
//! will be defined as &lt;name&gt;UPtr.
#define DECLARE_UNIQUE_PTR(name) struct name ## Deleter { void operator()(name *ptr) const; }; \
    using name ## UPtr = std::unique_ptr<name, name ## Deleter>

//! @brief Implements a custom deleter for a type declared using DECLARE_UNIQUE_PTR().
//! @param[in] name The name of the data type which needs a unique pointer.
#define IMPLEMENT_UNIQUE_PTR(name) void name ## Deleter::operator()(name *ptr) const { if (ptr) delete ptr; }

//! @brief Declares a unique pointer type with its own deleter.
//! @param[in] name The name of the type which needs a unique pointer, which
//! will be defined as &lt;name&gt;UPtr.
#define DECLARE_DERIVED_UNIQUE_PTR(name,baseName) using name ## UPtr = std::unique_ptr<name, baseName ## Deleter>

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
void *mallocAligned(size_t alignment, size_t sizeInBytes);
void *mallocAlignedPow2(uint8_t alignmentPow2, size_t sizeInBytes);
void freeAligned(void *alignedBlock);

size_t getPagedBlockSize();
void *allocatePagedBlock(size_t blockCount);
bool freePagedBlock(void *block, size_t blockCount, bool dontThrow);

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

//! @brief An object representing a read-only view of a contiguous set of objects.
//! @tparam T The data type of the objects being viewed.
template<typename T> class View
{
public:
    // Public Types
    using ValueType = typename T;
    using PointerType = typename ValueType *;
    using ReferenceType = typename ValueType &;
    using ConstPointerType = typename const ValueType *;
    using ConstReferenceType = typename const ValueType &;
    using VectorType = std::vector<ValueType>;
    using StringType = std::basic_string<ValueType>;
    using StringViewType = std::basic_string_view<ValueType>;
private:
    // Internal Fields
    PointerType _data;
    size_t _count;
public:
    // Construction/Destruction
    ~View() = default;

    //! @brief Constructs a view of 0 objects.
    View() :
        _data(nullptr),
        _count(0)
    {
    }

    //! @brief Constructs a view of a fixed number of objects.
    //! @param[in] data A pointer to the first object.
    //! @param[in] count The count of objects pointed to by @p data.
    View(PointerType data, size_t count) :
        _data(data),
        _count(count)
    {
        if ((count > 0) && (data == nullptr))
        {
            throw ArgumentNullException("data");
        }
    }

    //! @brief Constructs a view of a number of objects known at compile time.
    //! @tparam N The count of objects in the array.
    //! @param[in] data The array of objects to view.
    template<std::size_t N>
    View(ValueType(&rhs)[N]) :
        _data(rhs),
        _count(N)
    {
    }

    //! @brief Creates a view of the elements of a vector.
    //! @param[in] collection The collection to view.
    View(VectorType &collection) :
        _data(collection.data()),
        _count(collection.size())
    {
    }

    //! @brief Creates a view of the elements of a string, not including any
    //! terminating null character.
    //! @param[in] str The string to view.
    View(StringType &str) :
        _data(str.c_str()),
        _count(str.length())
    {
    }

    //! @brief Creates a view of the elements of a string view.
    //! @param[in] str The string to view.
    View(StringViewType &str) :
        _data(str.data()),
        _count(str.length())
    {
    }

    // Accessors

    //! @brief Determines if the view contains zero elements.
    bool isEmpty() const { return _count == 0; }

    //! @brief Gets the count of elements in the view.
    size_t getCount() const { return _count; }

    //! @brief Gets the count of bytes used by all elements in the view.
    size_t getByteCount() const { return _count * sizeof(ValueType); }

    //! @brief Gets a pointer to the first element in the view.
    PointerType getData() { return _data; }

    //! @brief Gets a pointer to the first element in the view.
    ConstPointerType getData() const { return _data; }

    //! @brief Allows subscript access to the elements of the view.
    //! @param[in] index The 0-based index of the item to obtain.
    //! @return A read-only reference to the specified object.
    //! @throws IndexOutOfRangeException Thrown if the value of @p index is invalid.
    ReferenceType &operator[](size_t index)
    {
        if (index < _count)
        {
            return _data[index];
        }

        throw IndexOutOfRangeException(index, _count);
    }

    //! @brief Allows subscript access to the elements of the view.
    //! @param[in] index The 0-based index of the item to obtain.
    //! @return A read-only reference to the specified object.
    //! @throws IndexOutOfRangeException Thrown if the value of @p index is invalid.
    ConstReferenceType &operator[](size_t index) const
    {
        if (index < _count)
        {
            return _data[index];
        }

        throw IndexOutOfRangeException(index, _count);
    }

    //! @brief Gets an iterator-compatible value representing the position of
    //! the first element in the view.
    PointerType begin() { return _data; }

    //! @brief Gets an iterator-compatible value representing the position of
    //! the element after the last one in the view.
    PointerType end() { return _data + _count; }

    //! @brief Gets an iterator-compatible value representing the position of
    //! the first element in the view.
    ConstPointerType begin() const { return _data; }

    //! @brief Gets an iterator-compatible value representing the position of
    //! the element after the last one in the view.
    ConstPointerType end() const { return _data + _count; }

    // Operations

    //! @brief Gets a subset of the view.
    //! @param[in] start The 0-based index of the first element in the subset view.
    //! @return A subset view containing all elements in the original view at or
    //! after the one at @p start.
    //! @throws IndexOutOfRangeException Thrown if @p start is beyond the end
    //! of the current view.
    View slice(size_t start) const
    {
        if (start < _count)
        {
            return View(_data + start, _count - start);
        }
        else
        {
            throw IndexOutOfRangeException(start, _count);
        }
    }

    //! @brief Gets a subset of the view.
    //! @param[in] start The 0-based index of the first element in the subset view.
    //! @param[in] count The count of elements to include in the subset.
    //! @return A subset view containing @p count elements from the original view
    //! starting with the one at @p start.
    //! @throws IndexOutOfRangeException Thrown if @p start is beyond the end
    //! of the current view or @p count attempt to create a view of items beyond
    //! the end of the current view.
    View slice(size_t start, size_t count) const
    {
        if (start < _count)
        {
            size_t maxCount = _count - start;

            if (count <= maxCount)
            {
                return View(_data + start, count);
            }
            else
            {
                throw IndexOutOfRangeException(count, _count);
            }
        }
        else
        {
            throw IndexOutOfRangeException(start, _count);
        }
    }

    //! @brief Creates a view of the current data, but expressed as raw bytes.
    View<uint8_t> toBytes() const
    {
        return View<uint8_t>(reinterpret_cast<uint8_cptr_t>(_data),
                             _count * sizeof(ValueType));
    }

    //! @brief Creates a new view of the same elements hosted in a different
    //! block of memory.
    //! @param[in] newSource The base address of the new first element.
    //! @return A view starting at @p newSource containing the same number of
    //! elements as the current view.
    View retarget(PointerType newSource) const
    {
        return View(newSource, _count);
    }

    //! @brief Creates a new view of the same elements hosted in a different
    //! block of memory.
    //! @param[in] originalSource The start of the block which the current object
    //! viewed a subset, not necessarily beginning at @p originalSource.
    //! @param[in] newSource The start of the block which will be a copy of
    //! @p oiginalSource to create a new view into.
    //! @return A new view which references a subset of @p newSource.
    View retarget(ConstPointerType originalSource, PointerType newSource) const
    {
        size_t originalOffset = _data - originalSource;

        return ConstView(newSource + originalOffset, _count);
    }

    //! @brief Copies the contents of the view to another array.
    //! @param[in] dest A pointer to the array to receive the copied values.
    //! @return A pointer to the destination element just after the last one copied.
    PointerType copyTo(PointerType dest) const
    {
        return std::copy_n(_data, _count, dest);
    }

    //! @brief Copies the contents of the view into an uninitialised array,
    //! using copy-construction on the new elements.
    //! @param[in] dest A pointer to the first element to overwrite.
    //! @return A pointer to the destination element just after the last one copied.
    PointerType copyConstructTo(PointerType dest) const
    {
        return std::uninitialized_copy_n(_data, _count, dest);
    }
};

//! @brief An object representing a read-only view of a contiguous set of objects.
//! @tparam T The data type of the objects being viewed.
template<typename T> class ConstView
{
public:
    // Public Types
    using ValueType = typename T;
    using PointerType = typename ValueType *;
    using ReferenceType = typename ValueType &;
    using ConstPointerType = typename const ValueType *;
    using ConstReferenceType = typename const ValueType &;
    using VectorType = std::vector<ValueType>;
    using StringType = std::basic_string<ValueType>;
    using StringViewType = std::basic_string_view<ValueType>;
private:
    // Internal Fields
    ConstPointerType _data;
    size_t _count;
public:
    // Construction/Destruction
    ~ConstView() = default;

    //! @brief Constructs a view of 0 objects.
    ConstView() :
        _data(nullptr),
        _count(0)
    {
    }

    //! @brief Constructs a read-only view of a writable view of objects.
    ConstView(const View<ValueType> &rhs) :
        _data(rhs.getData()),
        _count(rhs.getCount())
    {
    }

    //! @brief Constructs a view of a fixed number of objects.
    //! @param[in] data A pointer to the first object.
    //! @param[in] count The count of objects pointed to by @p data.
    ConstView(ConstPointerType data, size_t count) :
        _data(data),
        _count(count)
    {
        if ((count > 0) && (data == nullptr))
        {
            throw ArgumentNullException("data");
        }
    }

    //! @brief Constructs a view of a number of objects known at compile time.
    //! @tparam N The count of objects in the array.
    //! @param[in] data The array of objects to view.
    template<std::size_t N>
    ConstView(const ValueType (&rhs)[N]) :
        _data(rhs),
        _count(N)
    {
    }

    //! @brief Creates a view of the elements of a vector.
    //! @param[in] collection The collection to view.
    ConstView(const VectorType &collection) :
        _data(collection.data()),
        _count(collection.size())
    {
    }

    //! @brief Creates a view of the elements of a string, not including any
    //! terminating null character.
    //! @param[in] str The string to view.
    ConstView(const StringType &str) :
        _data(str.c_str()),
        _count(str.length())
    {
    }

    //! @brief Creates a view of the elements of a string view.
    //! @param[in] str The string to view.
    ConstView(const StringViewType &str) :
        _data(str.data()),
        _count(str.length())
    {
    }

    // Accessors

    //! @brief Determines if the view contains zero elements.
    bool isEmpty() const { return _count == 0; }

    //! @brief Gets the count of elements in the view.
    size_t getCount() const { return _count; }

    //! @brief Gets the count of bytes used by all elements in the view.
    size_t getByteCount() const { return _count * sizeof(ValueType); }

    //! @brief Gets a pointer to the first element in the view.
    ConstPointerType getData() const { return _data; }

    //! @brief Allows subscript access to the elements of the view.
    //! @param[in] index The 0-based index of the item to obtain.
    //! @return A read-only reference to the specified object.
    //! @throws IndexOutOfRangeException Thrown if the value of @p index is invalid.
    ConstReferenceType &operator[](size_t index) const
    {
        if (index < _count)
        {
            return _data[index];
        }

        throw IndexOutOfRangeException(index, _count);
    }

    //! @brief Gets an iterator-compatible value representing the position of
    //! the first element in the view.
    ConstPointerType begin() const { return _data; }

    //! @brief Gets an iterator-compatible value representing the position of
    //! the element after the last one in the view.
    ConstPointerType end() const { return _data + _count; }

    // Operations

    //! @brief Overwrites the current read-only view with the properties
    //! of a writable view.
    //! @param[in] rhs The writable view to assign to this one.
    //! @returns A reference to the current object.
    ConstView &operator=(const View<ValueType> &rhs)
    {
        _data = rhs.getData();
        _count = rhs.getCount();

        return *this;
    }

    //! @brief Gets a subset of the view.
    //! @param[in] start The 0-based index of the first element in the subset view.
    //! @return A subset view containing all elements in the original view at or
    //! after the one at @p start.
    //! @throws IndexOutOfRangeException Thrown if @p start is beyond the end
    //! of the current view.
    ConstView slice(size_t start) const
    {
        if (start < _count)
        {
            return ConstView(_data + start, _count - start);
        }
        else
        {
            throw IndexOutOfRangeException(start, _count);
        }
    }

    //! @brief Gets a subset of the view.
    //! @param[in] start The 0-based index of the first element in the subset view.
    //! @param[in] count The count of elements to include in the subset.
    //! @return A subset view containing @p count elements from the original view
    //! starting with the one at @p start.
    //! @throws IndexOutOfRangeException Thrown if @p start is beyond the end
    //! of the current view or @p count attempt to create a view of items beyond
    //! the end of the current view.
    ConstView slice(size_t start, size_t count) const
    {
        if (start < _count)
        {
            size_t maxCount = _count - start;

            if (count <= maxCount)
            {
                return ConstView(_data + start, count);
            }
            else
            {
                throw IndexOutOfRangeException(count, _count);
            }
        }
        else
        {
            throw IndexOutOfRangeException(start, _count);
        }
    }

    //! @brief Creates a view of the current data, but expressed as raw bytes.
    ConstView<uint8_t> toBytes() const
    {
        return ConstView<uint8_t>(reinterpret_cast<uint8_cptr_t>(_data),
                                  _count * sizeof(ValueType));
    }

    //! @brief Creates a new view of the same elements hosted in a different
    //! block of memory.
    //! @param[in] newSource The base address of the new first element.
    //! @return A view starting at @p newSource containing the same number of
    //! elements as the current view.
    ConstView retarget(ConstPointerType newSource) const
    {
        return ConstView(newSource, _count);
    }

    //! @brief Creates a new view of the same elements hosted in a different
    //! block of memory.
    //! @param[in] originalSource The start of the block which the current object
    //! viewed a subset, not necessarily beginning at @p originalSource.
    //! @param[in] newSource The start of the block which will be a copy of
    //! @p oiginalSource to create a new view into.
    //! @return A new view which references a subset of @p newSource.
    ConstView retarget(ConstPointerType originalSource, ConstPointerType newSource) const
    {
        size_t originalOffset = _data - originalSource;

        return ConstView(newSource + originalOffset, _count);
    }

    //! @brief Copies the contents of the view to another array.
    //! @param[in] dest A pointer to the array to receive the copied values.
    //! @return A pointer to the destination element just after the last one copied.
    PointerType copyTo(PointerType dest) const
    {
        return std::copy_n(_data, _count, dest);
    }

    //! @brief Copies the contents of the view into an uninitialised array,
    //! using copy-construction on the new elements.
    //! @param[in] dest A pointer to the first element to overwrite.
    //! @return A pointer to the destination element just after the last one copied.
    PointerType copyConstructTo(PointerType dest) const
    {
        return std::uninitialized_copy_n(_data, _count, dest);
    }
};

//! @brief An alias for a writable view of a contiguous run of bytes.
using ByteView = View<uint8_t>;

//! @brief An alias for a read-only view of a contiguous run of bytes.
using ByteConstView = ConstView<uint8_t>;

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
