//! @file ObjectGL/RenderContextPrivate.cpp
//! @brief The definition of the implementation of the inner RenderContext object.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"
#include "DisplayContextPrivate.hpp"
#include "RenderContextPrivate.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// RenderContextPrivate Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a render context which is a child of a specified display.
//! @param[in] display The inner pointer to the parent dispay.
RenderContextPrivate::RenderContextPrivate(const std::shared_ptr<DisplayContextPrivate> &display) :
    _display(display)
{
    if (display.operator bool() == false)
    {
        throw Ag::ArgumentException("display");
    }
}

//! @brief Gets a pointer to the owning display.
const std::shared_ptr<DisplayContextPrivate> &RenderContextPrivate::getDisplay() const
{
    return _display;
}

//! @brief Gets a read-only reference to the GL API resolved for the render 
//! device the object represents.
const GLAPI &RenderContextPrivate::getAPI() const
{
    return _api;
}

//! @brief Gets a writable reference to the GL API resolved for the render
//! device the object represents.
GLAPI &RenderContextPrivate::getAPIInternal()
{
    return _api;
}

////////////////////////////////////////////////////////////////////////////////
// AssignableRenderContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a RenderContext-derived object which is bound to an
//! existing implementation.
//! @param[in] context The inner render context to bind.
AssignableRenderContext::AssignableRenderContext(const RenderContextPrivateSPtr &context) :
    RenderContext(context)
{
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

