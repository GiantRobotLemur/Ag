//! @file Geometry/Transform2DStack.cpp
//! @brief The definition of a data structure which manages the successive
//! application of 2D affine transforms.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/Transform2DStack.hpp"
#include "Operations.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Transform2DStack Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a new transformation stack with a hint about its
//! required capacity.
//! @param[in] sizeHint The likely maximum number of transforms in the stack.
Transform2DStack::Transform2DStack(size_t sizeHint)
{
    _transforms.reserve(std::max(sizeHint, static_cast<size_t>(8)));
}

//! @brief Determines if there are any transformations in the stack.
//! @retval true The stack contains no transforms, getTop() will return an
//! identity transform.
//! @retval false The stack contains at least one transform.
bool Transform2DStack::isEmpty() const noexcept
{
    return _transforms.empty();
}

//! @brief Gets the transformation at the top of the stack or an identity
//! transform if the stack is empty.
const AffineTransform2D &Transform2DStack::getTop() const noexcept
{
    static const AffineTransform2D identity;

    return _transforms.empty() ? identity : _transforms.back();
}

//! @brief Pops all elements from the stack.
void Transform2DStack::clear()
{
    _transforms.clear();
}

//! @brief Restores the stack to a level it was at before a transform was
//! appended.
//! @param[in] level The value returned by a call to push() used to restore
//! the stack to the state before that transformation was appended.
void Transform2DStack::restore(size_t level)
{
    if (_transforms.size() > level)
    {
        _transforms.erase(_transforms.begin() + level, _transforms.end());
    }
}

//! @brief Pushes a new transform onto the stack - appending the transformation
//! to the previous stack top.
//! @param[in] transform The transformation to append.
//! @return The index of the appended transformation.
size_t Transform2DStack::push(const AffineTransform2D &transform)
{
    double newTop[6];
    size_t index = _transforms.size();

    if (_transforms.empty())
    {
        _transforms.push_back(transform);
    }
    else
    {
        Operations_AffineTrans2D::multiply(transform.toArray(),
                                           _transforms.back().toArray(),
                                           newTop);

        _transforms.emplace_back(newTop);
    }

    return index;
}

//! @brief Pops the transformation from the top of the stack.
void Transform2DStack::pop()
{
    if (_transforms.empty() == false)
        _transforms.pop_back();
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

