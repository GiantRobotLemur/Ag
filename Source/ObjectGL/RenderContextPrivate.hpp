//! @file ObjectGL/RenderContextPrivate.hpp
//! @brief The declaration of the implementation of the inner RenderContext object.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_RENDER_CONTEXT_PRIVATE_HPP__
#define __AG_OBJECT_GL_RENDER_CONTEXT_PRIVATE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Ag/ObjectGL/CommandSets.hpp"
#include "Ag/ObjectGL/RenderContext.hpp"

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
struct APIResolver;

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class DisplayContextPrivate;

//! @brief The implementation of the inner RenderContext object.
class RenderContextPrivate : public std::enable_shared_from_this<RenderContextPrivate>
{
protected:
    // Construction/Destruction
    RenderContextPrivate(const std::shared_ptr<DisplayContextPrivate> &display);
public:
    virtual ~RenderContextPrivate() = default;

    // Accessors
    const std::shared_ptr<DisplayContextPrivate> &getDisplay() const;
    const GLAPI &getAPI() const;

    // Operations
    void initialiseAPI(const APIResolver *resolver);

    // Overrideable
    virtual void makeCurrent() =0;
    virtual void doneCurrent() =0;
    virtual void swapBuffers() =0;
private:
    // Internal Fields
    std::shared_ptr<DisplayContextPrivate> _display;
    GLAPI _api;
};

//! @brief An alias for a shared pointer to an inner render context.
using RenderContextPrivateSPtr = std::shared_ptr< RenderContextPrivate>;

//! @brief An internal RenderContext object which allows an inner context to
//! be bound.
class AssignableRenderContext : public RenderContext
{
public:
    AssignableRenderContext(const RenderContextPrivateSPtr &context);
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
