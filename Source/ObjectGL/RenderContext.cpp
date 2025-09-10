//! @file ObjectGL/RenderContext.cpp
//! @brief The definition of an object representing an OpenGL context which can
//! create resources and render using them.
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
#include "Ag/ObjectGL/RenderContext.hpp"
#include "RenderContextPrivate.hpp"
#include "ResourceWrappers.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// RenderContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object bound to an inner render context.
//! @param[in] context A reference to the context to bind the object to.
RenderContext::RenderContext(const std::shared_ptr<RenderContextPrivate> &context) :
    _context(context)
{
}

//! @brief Indicates whether the object is bound to a renderer.
//! @retval true The object is bound to valid render context.
//! @retval false The object is in an unbound state.
bool RenderContext::isBound() const
{
    return _context.operator bool();
}

//! @brief Gets the OpenGL API which pertains to the current context.
const GLAPI &RenderContext::getAPI() const
{
    verifyAccess("getAPI()");

    return _context->getAPI();
}

//! @brief Gets an object which can resolve API entry points and detect
//! extensions on the current display device.
const APIResolver *RenderContext::getResolver() const
{
    verifyAccess("getResolver()");

    return _context->getDisplay()->getResolver();
}

//! @brief Selects the context for use on the current thread.
void RenderContext::makeCurrent()
{
    verifyAccess("makeCurrent()");

    _context->makeCurrent();
}

//! @brief De-selects any context for use on the current thread.
void RenderContext::doneCurrent()
{
    verifyAccess("doneCurrent()");

    _context->doneCurrent();
}

//! @brief Swaps the front and back buffers if in a double buffer system.
void RenderContext::swapBuffers()
{
    verifyAccess("swapBuffers()");

    _context->swapBuffers();
}

//! @brief Create a shader using the current context.
//! @param[in] type The type of shader to create.
//! @return An object wrapping the newly created shader.
Shader RenderContext::createShader(ShaderType type)
{
    verifyAccess("createShader()");

    auto &api = _context->getAPI();

    ShaderName name = api.createShader(type);
    auto resource = std::make_shared<ShaderResource>(_context->getDisplay(),
                                                        name);

    return AssignableShader(resource);
}

//! @brief Throws an exception if the object is in an unbound state.
//! @param[in] fnName The name of the function which the program was attempting
//! to perform.
//! @throws Ag::ObjectNotBoundException If the object is not bound to a valid
//! RenderContext resource.
void RenderContext::verifyAccess(const char *fnName) const
{
    if (!_context)
    {
        throw Ag::ObjectNotBoundException("Render Context", fnName);
    }
}

////////////////////////////////////////////////////////////////////////////////
// RenderScope Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Makes a context current for the lifetime of the object.
//! @param[in] context The context to select on the current thread.
RenderScope::RenderScope(const RenderContext &context) :
    _context(context)
{
    _context.makeCurrent();
}

//! @brief Calls doneCurrent() on the context the object was constructed with.
RenderScope::~RenderScope()
{
    _context.doneCurrent();
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

