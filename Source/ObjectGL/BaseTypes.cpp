//! @file ObjectGL/BaseTypes.cpp
//! @brief The definition of types which support OpenGL API groups and wrapper
//! command sets.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"
#include "Ag/ObjectGL/BaseTypes.hpp"
#include "Ag/ObjectGL/OpenGLException.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// PerEntryPoint Member Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets a reference to the function pointer described by the entry
//! within the structure being operated upon.
//! @param[in] entry A description of the entry point within a structure.
//! @return A reference to the function pointer within the structure being
//! operated upon.
void *&PerEntryPoint::getEntryPoint(const EntryOffset &entry)
{
    return *reinterpret_cast<void **>(reinterpret_cast<uint8_t *>(_basePtr) +
                                      entry.first);
}

//! @ Constructs an object to access function pointers in a specified structure.
//! @param[in] basePtr The base address of the data structure containing the
//! entry points to operate upon.
PerEntryPoint::PerEntryPoint(void *basePtr) :
    _basePtr(basePtr)
{
}

////////////////////////////////////////////////////////////////////////////////
// ClearEntryPoint Member Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a functor object which can set dynamic function entry
//! points to an empty value (nullptr).
//! @param[in] basePtr The base address of the data structure containing the
//! entry points to operate upon.
ClearEntryPoint::ClearEntryPoint(void *basePtr) :
    PerEntryPoint(basePtr)
{
}

//! @brief Sets the pointer to the described function to nullptr.
//! @param[in] entry An object describing the function entry point to blank.
void ClearEntryPoint::operator()(const EntryOffset &entry)
{
    getEntryPoint(entry) = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// ResolveEntryPoint Member Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a functor to resolve the address of an entry point.
//! @param[in] basePtr The base address of the data structure containing the
//! entry points to operate upon.
ResolveEntryPoint::ResolveEntryPoint(void *basePtr, const APIResolver *resolver) :
    PerEntryPoint(basePtr),
    _resolver(resolver)
{
}

//! @brief A functor which attempts to resolve the name of an entry point int
//! an address and write it back to the data structure being operated upon.
//! @param[in] entry An object describing the function entry point to resolve.
void ResolveEntryPoint::operator()(const EntryOffset &entry)
{
    getEntryPoint(entry) = _resolver->resolveEntryPoint(entry.second);
}

////////////////////////////////////////////////////////////////////////////////
// BaseAPI Member Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which will define a dynamic API resolved at runtime.
BaseAPI::BaseAPI() :
    _getError(nullptr)
{
}

//! @brief An action performed before a raw API command is executed.
//! @param[in] commandName The name of the command about to be executed.
//! @param[in] entryPoint A pointer to the command function about to be called.
void BaseAPI::beforeCommand(const char *commandName, const void *entryPoint) const
{
    if (entryPoint != nullptr)
        return;

    std::string message;
    message.assign("The command '");
    message.append(commandName);
    message.append("()'");

    throw Ag::NotSupportedException(message.c_str());
}

//! @brief An action performed after a raw API command has been executed.
//! @param[in] commandName The name of the command which was executed.
void BaseAPI::afterCommand(const char *commandName) const
{
    constexpr size_t RetryCount = 9;
    constexpr unsigned int GL_NO_ERROR = 0;
    unsigned int errorCodes[RetryCount];
    size_t errorCount = 0;

    // Accumulate error codes until all are cleared or we reach
    // the retry count - should never happen, but we don't want
    // to loop forever, do we?
    int currentError = _getError();
    int prevError = GL_NO_ERROR;

    while ((currentError != GL_NO_ERROR) &&
           (currentError != prevError) &&
           (errorCount < RetryCount))
    {
        errorCodes[errorCount++] = currentError;
        prevError = currentError;
        currentError = _getError();
    }

    if (errorCount > 0)
    {
        std::sort(errorCodes, errorCodes + errorCount);
        unsigned int *lastError = std::unique(errorCodes, errorCodes + errorCount);
        unsigned int *firstError = errorCodes;

        // Skip the error codes which were GL_NO_ERROR (0)
        for (firstError = errorCodes;
             (firstError != lastError) && (*firstError == 0);
             ++firstError)
        {
            // Deliberately empty.
        }

        if (firstError != lastError)
        {
            throw OpenGLException(commandName, firstError,
                                  static_cast<size_t>(lastError - firstError));
        }
    }
}

//! @brief Updates the getError() function pointer.
//! @param[in] resolver An object which can look up functions by name.
void BaseAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _getError = resolver->getErrorReporterProc();
    }
}

////////////////////////////////////////////////////////////////////////////////
// BaseExtension Member Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which will define a dynamic extension API
//! resolved at runtime.
//! @param[in] extName The text used to identify the existence of the API in a
//! specific context.
BaseExtension::BaseExtension(const char *extName) :
    _extName(extName),
    _isPresent(false)
{
}

//! @brief Determines if the extension was available in the context of the
//! last call to resolve().
//! @retval true The extension was present the last time resolve() was called.
//! @retval false The extension was not present the last time resolve was called
//! or the API has never been resolved.
bool BaseExtension::isPresent() const
{
    return _isPresent;
}

//! @brief Updates the availability of the API.
//! @param[in] resolver An object which can look up functions by name.
void BaseExtension::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _isPresent = resolver->isExtensionPresent(_extName);

        // Call the base class.
        BaseAPI::resolve(resolver);
    }
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

