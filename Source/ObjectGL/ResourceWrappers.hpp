//! @file Ag/ObjectGL/ResourceWrappers.hpp
//! @brief The declaration of a number of internal classes which wrap OpenGL
//! resources.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_RESOURCE_WRAPPERS_HPP__
#define __AG_OBJECT_GL_RESOURCE_WRAPPERS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Ag/Core/Exception.hpp"
#include "Ag/ObjectGL/EnumTypes.hpp"
#include "Ag/ObjectGL/Identifiers.hpp"
#include "Ag/ObjectGL/Buffer.hpp"
#include "Ag/ObjectGL/Program.hpp"
#include "Ag/ObjectGL/Shader.hpp"
#include "DisplayContextPrivate.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A template for a shareable object which wraps an OpenGL resource.
//! @tparam TName The data type of the object identifying the resource.
template<typename TName>
class BaseResource : public std::enable_shared_from_this<BaseResource<TName>>
{
public:
    // Construction/Destruction
    //! @brief Constructs a shareable object to represent a named resource.
    //! @param[in] display The display which owns the resource.
    //! @param[in] name The identifier of the resource to wrap.
    BaseResource(DisplayContextPrivateSPtr display, const TName &name) :
        _display(display),
        _name(name)
    {
        // Ensure the object has a valid state.
        if (name.ID == 0)
        {
            throw Ag::ArgumentException("name");
        }
        else if (!display)
        {
            throw Ag::ArgumentException("display");
        }
    }

    //! @brief Ensures that the resource is scheduled for destruction.
    ~BaseResource()
    {
        if (_display && (_name.ID != 0))
        {
            _display->dispose(_name);
            _name.ID = 0;
        }
    }

    // Accessors
    //! @brief Gets the identifier of the underlying resource.
    TName getName() const { return _name; }

    //! @brief Gets the display which owns the resource.
    const DisplayContextPrivateSPtr &getDisplay() const { return _display; }
private:
    // Internal Fields
    DisplayContextPrivateSPtr _display;
    TName _name;
};

//! @brief A shareable object wrapping an OpenGL shader resource.
class ShaderResource : public BaseResource<ShaderName>
{
public:
    // Construction/Destruction
    //! @brief Constructs a shareable object to represent a shader component.
    //! @param[in] display A reference to the display the resource belongs to.
    //! @param[in] name The identifier of the resource.
    ShaderResource::ShaderResource(DisplayContextPrivateSPtr display,
                                   const ShaderName &name) :
        BaseResource(display, name)
    {
    }

    ~ShaderResource() = default;
};

//! @brief A class derived from Shader which can be initialised with a resource.
class AssignableShader : public Shader
{
public:
    AssignableShader(const std::shared_ptr<ShaderResource> &resource) :
        Shader(resource)
    {
    }
};

//! @brief A shareable object wrapping an OpenGL Program resource.
class ProgramResource : public BaseResource<ProgramName>
{
public:
    // Construction/Destruction
    //! @brief Constructs a shareable object to represent a Program component.
    //! @param[in] display A reference to the display the resource belongs to.
    //! @param[in] name The identifier of the resource.
    ProgramResource::ProgramResource(DisplayContextPrivateSPtr display,
                                     const ProgramName &name) :
        BaseResource(display, name)
    {
    }

    ~ProgramResource() = default;
};

//! @brief A class derived from Program which can be initialised with a resource.
class AssignableProgram : public Program
{
public:
    AssignableProgram(const std::shared_ptr<ProgramResource> &resource) :
        Program(resource)
    {
    }
};

//! @brief A shareable object wrapping an OpenGL Buffer resource.
class BufferResource : public BaseResource<BufferName>
{
public:
    // Construction/Destruction
    //! @brief Constructs a shareable object to represent a Program component.
    //! @param[in] display A reference to the display the resource belongs to.
    //! @param[in] name The identifier of the resource.
    BufferResource::BufferResource(DisplayContextPrivateSPtr display,
                                   const BufferName &name) :
        BaseResource(display, name)
    {
    }

    ~BufferResource() = default;
};

//! @brief A class derived from Buffer which can be initialised with a resource.
class AssignableBuffer : public Buffer
{
public:
    AssignableBuffer(const std::shared_ptr<BufferResource> &resource) :
        Buffer(resource)
    {
    }
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
