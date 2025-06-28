//! @file Ag/Geometry/Point2ICollectionView.hpp
//! @brief The declaration of an object holding a view of Point2I values without
//! owning them so that optimised operations can be performed on groups of
//! elements.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_POINT2I_COLLECTION_VIEW_HPP__
#define __AG_GEOMETRY_POINT2I_COLLECTION_VIEW_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Point2I.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object holding a view of Point2I values without
//! owning them so that optimised operations can be performed on groups of
//! elements.
class Point2ICollectionView
{
public:
    // Public Data Types
    using ValuePtr = Point2I *;
    using ValueCPtr = const Point2I *;
    using Collection = Point2ICollection;
    using CollectionRef = Point2ICollection &;
    using CollectionCRef = const Point2ICollection &;

    // Construction/Destruction
    //! @brief Constructs an empty collection view.
    constexpr Point2ICollectionView() noexcept : _source(nullptr), _count(0) { }
    ~Point2ICollectionView() = default;

    // Accessors
    constexpr bool isEmpty() const noexcept { return _count == 0; }

private:
    // Internal Fields
    ValueCPtr _source;
    size_t _count;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
