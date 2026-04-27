//! @file Ag/Geometry/Transform2DStack.hpp
//! @brief The declaration of a data structure which manages the successive
//! application of 2D affine transforms.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_TRANSFORM_2D_STACK_HPP__
#define __AG_GEOMETRY_TRANSFORM_2D_STACK_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "AffineTransform2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A data structure which manages the successive application of 2D
//! affine transforms.
class Transform2DStack
{
public:
    // Construction/Destruction
    Transform2DStack() = default;
    Transform2DStack(size_t sizeHint);
    ~Transform2DStack() = default;

    // Accessors
    bool isEmpty() const noexcept;
    const AffineTransform2D &getTop() const noexcept;

    // Operations
    void clear();
    void restore(size_t level);
    size_t push(const AffineTransform2D &transform);
    void pop();
private:
    // Internal Fields
    AffineTransform2DCollection _transforms;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
