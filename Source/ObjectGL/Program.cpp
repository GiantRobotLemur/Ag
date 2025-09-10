//! @file ObjectGL/Program.cpp
//! @brief The definition of an object wrapping an OpenGL program resource.
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
#include "Ag/Core/Utils.hpp"
#include "Ag/ObjectGL/CommandSets.hpp"
#include "Ag/ObjectGL/Program.hpp"
#include "ResourceWrappers.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Program Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a program object already bound to an underlying resource.
//! @param[in] resource The resource to bind to.
Program::Program(const std::shared_ptr<ProgramResource> &resource) :
    _program(resource)
{
}

//! @brief Gets whether the object is bound to a valid underlying resource.
bool Program::isBound() const
{
    return _program.operator bool();
}

//! @brief Gets the identifier of the shader program, possibly an empty value
//! if the object is in an unbound state.
ProgramName Program::getName() const
{
    return (_program) ? _program->getName() : ProgramName();
}

//! @brief Gets the count of vertex attributes used by the program.
size_t Program::getActiveAttribCount() const
{
    size_t attribCount = 0;

    if (_program)
    {
        auto &api = _program->getDisplay()->getAPI();

        GLint count = 0;
        api.getProgramIV(_program->getName(),
                         ProgramPropertyARB::ActiveAttributes, &count);

        if (count > 0)
        {
            attribCount = static_cast<size_t>(count);
        }
    }

    return attribCount;
}

//! @brief Gets information about an attribute within a program.
//! @param[in] index The 0-based index of the attribute to query.
//! @param[out] info Receives attribute metadata.
void Program::getActiveAttrib(size_t index, ProgramAttribInfo &info) const
{
    // Clear the attribute information before any exception can be thrown.
    info.Name = Ag::String::Empty;
    info.DataType = AttributeType::Int;
    info.Size = 0;
    info.Location = -1;

    // Organise a buffer to receive the name.
    auto &api = verifyAccess("getActiveAttrib()");
    ProgramName id = _program->getName();
    const size_t BufferSize = 256;
    char buffer[BufferSize];
    std::vector<char> expandingBuffer;

    size_t bufferSize = BufferSize;
    char *effectiveBuffer = buffer;

    GLint maxSize = 0;

    api.getProgramIV(id, ProgramPropertyARB::ActiveAttributeMaxLength, &maxSize);

    if ((maxSize > 0) && (static_cast<size_t>(maxSize) > BufferSize))
    {
        bufferSize = static_cast<size_t>(maxSize);
        expandingBuffer.resize(bufferSize, '\0');
        effectiveBuffer = expandingBuffer.data();
    }

    GLsizei length = 0;

    api.getActiveAttrib(id, static_cast<GLint>(index),
                        static_cast<GLsizei>(bufferSize), &length, &info.Size,
                        &info.DataType, effectiveBuffer);

    if (length > 0)
    {
        info.Name = Ag::String(effectiveBuffer, static_cast<size_t>(length));
        info.Location = api.getAttribLocation(id, effectiveBuffer);
    }
}

//! @brief Gets metadata on all active attributes in a linked program.
//! @return A collection of attributes, possibly empty.
ProgramAttribCollection Program::getActiveAttribs() const
{
    auto &api = verifyAccess("getActiveAttribs()");
    ProgramName id = _program->getName();
    GLint value = 0;

    api.getProgramIV(id, ProgramPropertyARB::ActiveAttributes, &value);

    ProgramAttribCollection attribs;

    if (value > 0)
    {
        GLint count = value;
        std::vector<char> nameBuffer;
        attribs.reserve(static_cast<size_t>(count));

        // Gets the maximum size of any attribute name.
        api.getProgramIV(id, ProgramPropertyARB::ActiveAttributeMaxLength, &value);

        nameBuffer.resize((value > 0) ? static_cast<size_t>(value) : 256u, '\0');

        for (GLint i = 0; i < count; ++i)
        {
            auto &item = attribs.emplace_back();
            GLsizei nameLength = 0;

            api.getActiveAttrib(id, i, static_cast<GLsizei>(nameBuffer.size()),
                                &nameLength, &item.Size, &item.DataType,
                                nameBuffer.data());

            if (nameLength > 0)
            {
                item.Name = Ag::String(nameBuffer.data(),
                                       static_cast<size_t>(nameLength));

                item.Location = api.getAttribLocation(id, nameBuffer.data());
            }
        }
    }

    return attribs;
}

//! @brief Gets the count of uniforms active in the linked program.
size_t Program::getActiveUniformCount() const
{
    size_t uniformCount = 0;

    if (_program)
    {
        auto &api = _program->getDisplay()->getAPI();
        ProgramName id = _program->getName();
        GLint value = 0;

        api.getProgramIV(id, ProgramPropertyARB::ActiveUniforms, &value);

        if (value > 0)
        {
            uniformCount = static_cast<size_t>(value);
        }
    }

    return uniformCount;
}

//! @brief Gets information about a uniform referenced in a linked program.
//! @param[in] index The 0-based index of the uniform to query.
//! @param[out] info Receives uniform metadata.
void Program::getActiveUniform(size_t index, ProgramUniformInfo &info) const
{
    // Clear the attribute information before any exception can be thrown.
    info.Name = Ag::String::Empty;
    info.DataType = UniformType::Int;
    info.Size = 0;
    info.Location = -1;

    // Organise a buffer to receive the name.
    auto &api = verifyAccess("getActiveUniform()");
    ProgramName id = _program->getName();
    const size_t BufferSize = 256;
    char buffer[BufferSize];
    std::vector<char> expandingBuffer;

    size_t bufferSize = BufferSize;
    char *effectiveBuffer = buffer;

    GLint maxSize = 0;

    api.getProgramIV(id, ProgramPropertyARB::ActiveUniformMaxLength, &maxSize);

    if ((maxSize > 0) && (static_cast<size_t>(maxSize) > BufferSize))
    {
        bufferSize = static_cast<size_t>(maxSize);
        expandingBuffer.resize(bufferSize, '\0');
        effectiveBuffer = expandingBuffer.data();
    }

    GLsizei length = 0;

    api.getActiveUniform(id, static_cast<GLint>(index),
                         static_cast<GLsizei>(bufferSize), &length, &info.Size,
                         &info.DataType, effectiveBuffer);

    if (length > 0)
    {
        info.Name = Ag::String(effectiveBuffer, static_cast<size_t>(length));
        info.Location = api.getUniformLocation(id, effectiveBuffer);
    }
}

//! @brief Gets metadata on all active uniforms in the linked program.
ProgramUniformCollection Program::getActiveUniforms() const
{
    auto &api = verifyAccess("getActiveUniforms()");
    ProgramName id = _program->getName();
    GLint value = 0;

    api.getProgramIV(id, ProgramPropertyARB::ActiveUniforms, &value);

    ProgramUniformCollection uniforms;

    if (value > 0)
    {
        GLint count = value;
        std::vector<char> nameBuffer;
        uniforms.reserve(static_cast<size_t>(count));

        // Gets the maximum size of any uniform name.
        api.getProgramIV(id, ProgramPropertyARB::ActiveUniformMaxLength, &value);

        nameBuffer.resize((value > 0) ? static_cast<size_t>(value) : 256u, '\0');

        for (GLint i = 0; i < count; ++i)
        {
            auto &item = uniforms.emplace_back();
            GLsizei nameLength = 0;

            api.getActiveUniform(id, i, static_cast<GLsizei>(nameBuffer.size()),
                                 &nameLength, &item.Size, &item.DataType,
                                 nameBuffer.data());

            if (nameLength > 0)
            {
                item.Name = Ag::String(nameBuffer.data(),
                                       static_cast<size_t>(nameLength));

                item.Location = api.getUniformLocation(id, nameBuffer.data());
            }
        }
    }

    return uniforms;
}

//! @brief Gets the log produced by the last call to link().
Ag::String Program::getInfoLog() const
{
    if (_program)
    {
        auto &api = _program->getDisplay()->getAPI();
        GLint length = 0;

        ProgramName id = _program->getName();
        api.getProgramIV(id, ProgramPropertyARB::InfoLogLength, &length);

        if (length > 0)
        {
            size_t bufferSize = static_cast<size_t>(length);
            std::vector<char> buffer;
            GLsizei actualLength = 0;

            buffer.resize(bufferSize, '\0');
            api.getProgramInfoLog(id, static_cast<GLsizei>(bufferSize),
                                  &actualLength, buffer.data());

            if (actualLength > 0)
            {
                return Ag::String(buffer.data(),
                                  static_cast<size_t>(actualLength));
            }
        }
    }

    return Ag::String::Empty;
}

//! @brief Links the attached shaders together into a single program.
//! @retval true The program was successfully linked.
//! @retval false The link failed and a log was produced.
bool Program::link()
{
    auto &api = verifyAccess("link()");

    ProgramName id = _program->getName();

    api.linkProgram(id);

    GLint linkStatus = 0;
    api.getProgramIV(id, ProgramPropertyARB::LinkStatus, &linkStatus);

    return linkStatus != 0;
}

//! @brief Selects the program for use, i.e. glUseProgram(id).
void Program::select()
{
    auto &api = verifyAccess("select()");
    api.useProgram(_program->getName());
}

//! @brief De-selects the program for use, i.e. glUseProgram(0).
void Program::deselect()
{
    auto &api = verifyAccess("select()");

    ProgramName empty;
    api.useProgram(empty);
}


//! @brief Attaches a shader to the program so that it can be linked to it.
//! @param[in] shader The shader to attach.
void Program::attachShader(const Shader &shader)
{
    if (shader.isBound())
    {
        throw Ag::ArgumentException("shader");
    }

    auto &api = verifyAccess("attachShader()");

    api.attachShader(_program->getName(), shader.getName());
}

//! @brief Detaches a shader to the program so that it can be disposed of.
//! @param[in] shader The shader to detach.
void Program::detachShader(const Shader &shader)
{
    if (shader.isBound())
    {
        throw Ag::ArgumentException("shader");
    }

    auto &api = verifyAccess("detachShader()");

    api.detachShader(_program->getName(), shader.getName());
}

//! @brief Verifies that the object is associated with a valid resource and
//! returns an API used to operate on it.
//! @param[in] operation The name of the operation being performed.
//! @return A reference to an OpenGL API used to manipulate the resource.
//! @throws Ag::ObjectNotBoundException If the object is not bound to a
//! valid resource.
const GLAPI &Program::verifyAccess(const char *operation) const
{
    if (_program)
    {
        return _program->getDisplay()->getAPI();
    }
    else
    {
        throw Ag::ObjectNotBoundException("Shader", operation);
    }
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

