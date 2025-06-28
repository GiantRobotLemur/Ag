//! @file Ag/Core/CollectionTools.hpp
//! @brief The declaration of various useful collection-related template data
//! structures and functions.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_COLLECTION_TOOLS_HPP__
#define __AG_CORE_COLLECTION_TOOLS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <atomic>
#include <vector>

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an immutable static mapping from constant data.
//! @tparam TKey The data type of keys used to look up values.
//! @tparam TValue The data type of values being indexed.
//! @tparam TKeyComp An object used to perform less-than comparisons on
//! TKey objects.
//! @remarks Creates map from an array of std::pair<TKey, TValue> elements.
template<typename TKey, typename TValue, typename TKeyComp = std::less<TKey>>
class StaticMap
{
public:
    using MappingType = std::pair<TKey, TValue>;
    using MappingCPtr = const MappingType *;
private:
    struct KeyCompare
    {
        bool operator()(const MappingType &lhs, const MappingType &rhs) const
        {
            TKeyComp KeyComparer;

            return KeyComparer(lhs.first, rhs.first);
        }
    };

    const MappingType *_mappings;
    size_t _count;

public:
    //! @brief Constructs a map from a static array with a fixed size.
    //! @tparam TCount The count of elements in the array.
    //! @param[in] mappings The array to be sorted into an index.
    template<size_t TCount>
    StaticMap(MappingType(&mappings)[TCount]) :
        _mappings(mappings),
        _count(TCount)
    {
        std::sort(mappings, mappings + TCount, KeyCompare());
    }

    //! @brief Constructs a map from a static array with a specified size.
    //! @param[in] mappings The array to be sorted into an index.
    //! @param[in] count The count of elements in @p count.
    //! @remarks The @p mappings array will be sorted according to the
    //! key elements.
    StaticMap(MappingType *mappings, size_t count) :
        _mappings(mappings),
        _count(count)
    {
        std::sort(mappings, mappings + count, KeyCompare());
    }

    //! @brief Attempts to find the index of a mapping matching a key.
    //! @param[in] key The key to look up.
    //! @param[out] index Receives the index of the matching mapping, if any.
    //! @retval true If a matching mapping was found.
    //! @retval false If no mapping had a matching key.
    bool tryFindValue(const TKey &key, size_t &index) const
    {
        // Create a pointer to a mapping from just the key knowing that
        // the value element of the pair will NEVER be accessed.
        MappingCPtr keyMapping = reinterpret_cast<MappingCPtr>(&key);

        auto pos = std::lower_bound(_mappings, _mappings + _count,
                                    *keyMapping, KeyCompare());

        if (TKeyComp()(key, pos->first) == false)
        {
            index = std::distance(_mappings, pos);
            return true;
        }
        else
        {
            index = _count;
            return false;
        }
    }

    //! @brief Gets the value at a specified index
    //! @param[in] index The 0-based index of the mapping to extract
    //! a value from.
    //! @return A reference to the value in the mapping.
    const TValue &getValue(size_t index) const
    {
        return _mappings[index].second;
    }
};

//! @brief An equivalent of std::pair<iterator> which can be used with
//! range-based for loops.
//! @tparam TIterator The data type of the iterators defining the range.
template<typename TIterator> struct IteratorRange
{
    // Public Types
    using Iterator = TIterator;
    using ValueType = typename TIterator::value_type;

    // Public Fields
    Iterator Begin;
    Iterator End;

    // Construction/Destruction
    IteratorRange() = default;
    ~IteratorRange() = default;

    //! @brief Constructs an empty range with both Begin and End set to the
    //! same position.
    //! @param noRange The beginning and end position value.
    IteratorRange(const Iterator &noRange) :
        Begin(noRange),
        End(noRange)
    {
    }

    //! @brief Constructs an active range.
    //! @param first The position of the first item in the range.
    //! @param afterLast The position of the item after the last in the range.
    IteratorRange(const Iterator &first, const Iterator &afterLast) :
        Begin(first),
        End(afterLast)
    {
    }

    //! @brief Converts an std::pair of iterators to an IteratorRange object.
    //! @param[in] stdPair The pair of iterators to convert, first mapping to Begin
    //! and second mapping to End.
    IteratorRange(const std::pair<Iterator, Iterator> &stdPair) :
        Begin(stdPair.first),
        End(stdPair.second)
    {
    }

    //! @brief Overwrites the object from an std::pair of iterators.
    //! @param[in] stdPair The pair of iterators to convert, first mapping to Begin
    //! and second mapping to End.
    //! @return A reference to the current object.
    IteratorRange &operator=(const std::pair<Iterator, Iterator> &stdPair)
    {
        Begin = stdPair.first;
        End = stdPair.second;

        return *this;
    }

    //! @brief Determines if the range is empty.
    //! @retval true The Begin and End iterators are identical, so no items
    //! would be iterated over.
    //! @retval false The Begin and End iterators are different, suggesting
    //! that the range defines a non-empty set of items.
    bool isEmpty() const { return Begin == End; }

    //! @brief Determines the count of items in the run using the
    //! std::distance() function.
    size_t getCount() const { return static_cast<size_t>(std::distance(Begin, End)); }

    //! @brief Gets the position of the first element in the range.
    //! @note This member function is defined for compatibility with
    //! range-based for loops.
    const Iterator &begin() const { return Begin; }

    //! @brief Gets the position after the last element in the range.
    //! @note This member function is defined for compatibility with
    //! range-based for loops.
    const Iterator &end() const { return End; }

    //! @brief Gets a reference to the first element in the range.
    ValueType &front() { return *Begin; }

    //! @brief Gets a read-only reference to the first element in the range.
    const ValueType &front() const { return *Begin; }
};

//! @brief Finds the first group in a sorted set of items.
//! @tparam TItem The data type of the items in the set.
//! @tparam TIterator The data type of the iterator used to defined positions
//! of items in the set.
//! @tparam TPred The data type of the predicate used to compare set items.
//! @param[in] begin The iterator pointing to the first time in the set.
//! @param[in] end The iterator pointing to the item after the last in the set.
//! @param[out] groupRange Receives a range of iterators describing the
//! first identical group in the set based on the predicate test.
//! @param[in] predicate The predicate used to compare items in the set.
//! @retval true An initial group was found and returned in groupRange.
//! @retval false The set was empty, groupRange was set to an empty state.
template<typename TIterator, typename TItem = typename TIterator::value_type,
    typename TPred = std::less<TItem> >
bool getFirstGroup(const TIterator &begin, const TIterator &end,
                   IteratorRange<TIterator> &groupRange,
                   const TPred &predicate = std::less<TItem>())
{
    bool hasGroup = false;

    if (begin == end)
    {
        // The range is empty.
        groupRange = IteratorRange<TIterator>(end);
    }
    else
    {
        groupRange.Begin = begin;
        groupRange.End = std::upper_bound(begin, end, *begin, predicate);
        hasGroup = true;
    }

    return hasGroup;
}

//! @brief Finds the next group of identical items in a sorted set.
//! @tparam TItem The data type of the items in the set.
//! @tparam TIterator The data type of the iterator used to defined positions
//! of items in the set.
//! @tparam TPred The data type of the predicate used to compare set items.
//! @param[in] end The iterator pointing to the item after the last in the set.
//! @param[in,out] groupRange Holds the range of values in the previous group
//! and is updated with a range of iterators describing the
//! next identical group in the set based on the predicate test.
//! @param[in] predicate The predicate used to compare items in the set.
//! @retval true Another group was found and returned in groupRange.
//! @retval false There were no more groups in the set, groupRange was set to
//! an empty state.
template<typename TIterator, typename TItem = typename TIterator::value_type,
    typename TPred = std::less<TItem> >
bool getNextGroup(const TIterator &end,
                  IteratorRange<TIterator> &groupRange,
                  const TPred &predicate = std::less<TItem>())
{
    bool hasGroup = false;

    if (groupRange.Begin != end)
    {
        // We have at least an (initially) active range.
        if (groupRange.End == end)
        {
            // We must end the range without accessing the item.
            groupRange.Begin = end;
        }
        else
        {
            // Find the end of the next group by searing the remaining sub-set.
            groupRange.Begin = groupRange.End;
            groupRange.End = std::upper_bound(groupRange.Begin, end,
                                              *groupRange.Begin, predicate);

            hasGroup = true;
        }
    }

    return hasGroup;
}

//! @brief Extracts values from a collection of mappings, i.e the second member
//! of each mapping pair.
//! @tparam TValue The data type of values to be extracted.
//! @tparam TMappingIterator An iterator which points to values of type
//! std::pair<?, TValue>.
//! @param[in] range The range of mappings to extract values from.
//! @param[out] values A collection to receive the extracted values.
//! @retval true At least one value was extracted from the mappings.
//! @retval false The range was empty.
template<typename TMappingIterator, typename TValue>
bool getGroupValues(const IteratorRange<TMappingIterator> &range,
                    std::vector<TValue> &values)
{
    values.clear();
    size_t count = range.getCount();

    if (values.capacity() < count)
    {
        values.reserve(count);
    }

    for (const auto &item : range)
    {
        values.push_back(item.second);
    }

    return count > 0;
}

//! @brief Adds a run of elements to a vector, ensuring enough space has been
//! allocated before hand.
//! @tparam TValue The data type of the values stored in the vector.
//! @tparam TIter The data type of the iterator referencing new values.
//! @param[in] collection The collection to append the new elements to.
//! @param[in] begin The iterator referencing the first item to append.
//! @param[in] end The iterator after the last item to append.
//! @return The count of elements added to @p collection.
template<typename TValue, typename TIter>
size_t bulkAppend(std::vector<TValue> &collection, TIter begin, TIter end)
{
    if (begin == end)
        return 0;

    size_t count = std::distance(begin, end);
    size_t originalSize = collection.size();
    size_t requiredSize = originalSize + count;

    if (collection.capacity() < requiredSize)
        collection.reserve(requiredSize);

    for (TIter current = begin; current != end; ++current)
    {
        collection.emplace_back(*current);
    }

    return collection.size() - originalSize;
}

//! @brief Ensures a vector has capacity for a specified number of elements.
//! @tparam TCollection The data type of vector to extend.
//! @param[in] collection The vector to ensure the capacity of.
//! @param[in] totalCapacity The total number of elements the vector needs
//! to be able to hold.
template<typename TCollection>
void ensureCapacity(TCollection &collection, size_t totalCapacity)
{
    if (collection.capacity() < totalCapacity)
        collection.reserve(totalCapacity);
}

//! @brief Ensures a vector has capacity to append a specified number of 
//! additional elements.
//! @tparam TCollection The data type of vector to extend.
//! @param[in] collection The vector to ensure the capacity of.
//! @param[in] extraCapacity The count of additional elements the vector needs
//! to be able to hold.
template<typename TCollection>
void ensureExtraCapacity(TCollection &collection, size_t extraCapacity)
{
    size_t requiredSize = collection.size() + extraCapacity;

    if (collection.capacity() < requiredSize)
        collection.reserve(requiredSize);
}

//! @brief Calculates a difference between values.
//! @tparam T The data type of the values being compared..
//! @param[in] lhs The first value to compare.
//! @param[in] rhs The second value to compare.
//! @param[out] diff Receives the result of the comparison, -1 if
//! @p lhs is less than @p rhs, 0 if they are equal and 1 if
//! @p lhs is greater than @p rhs.
//! @retval true The values differ.
//! @retval false The values were the same.
template<typename T>
bool diffValues(T lhs, T rhs, int &diff)
{
    diff = (lhs == rhs) ? 0 : ((lhs < rhs) ? -1 : 1);

    return diff != 0;
}

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
