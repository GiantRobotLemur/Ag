//! @file Sdl3Tools/PropertySet.cpp
//! @brief The definition of an object wrapping the SDL_PropertiesID handle.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/PropertySet.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
template<typename T>
T getIntegerProperty(SDL_PropertiesID id, utf8_cptr_t name, T defaultValue)
{
    int64_t rawValue = static_cast<int64_t>(defaultValue);

    if (id != 0)
    {
        rawValue = SDL_GetNumberProperty(id, name, rawValue);
    }

    return static_cast<T>(rawValue);
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// PropertySet Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which is not bound to an underlying property set.
PropertySet::PropertySet() :
    _setId(0)
{
}

//! @brief Constructs an object which creates a copy of a property set.
//! @param[in] rhs The property set to copy.
PropertySet::PropertySet(const PropertySet &rhs) :
    _setId(0)
{
    clone(rhs);
}

//! @brief Takes ownership of a property set from another wrapper object.
//! @param[in] rhs The object to transfer a property set from.
PropertySet::PropertySet(PropertySet &&rhs) noexcept :
    _setId(0)
{
    std::exchange(_setId, rhs._setId);
}

//! @brief Constructs an object to wrap an existing property set.
//! @param[in] propertySetID The identifier of the property set.
PropertySet::PropertySet(SDL_PropertiesID propertySetID) :
    _setId(propertySetID)
{
}

//! @brief Ensures any wrapped property set is destroyed.
PropertySet::~PropertySet()
{
    dispose();
}

//! @brief Gets the value of a boolean property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
bool PropertySet::getBoolean(utf8_cptr_t name, bool defaultValue) const
{
    return (_setId == 0) ? defaultValue :
                           SDL_GetBooleanProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a 32-bit floating point property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
float PropertySet::getFloat(utf8_cptr_t name, float defaultValue) const
{
    return (_setId == 0) ? defaultValue :
                           SDL_GetFloatProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a signed 8-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
int8_t PropertySet::getInt8(utf8_cptr_t name, int8_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of an unsigned 8-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
uint8_t PropertySet::getUint8(utf8_cptr_t name, uint8_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a signed 16-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
int16_t PropertySet::getInt16(utf8_cptr_t name, int16_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of an unsigned 16-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
uint16_t PropertySet::getUint16(utf8_cptr_t name, uint16_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a signed 32-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
int32_t PropertySet::getInt32(utf8_cptr_t name, int32_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of an unsigned 32-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
uint32_t PropertySet::getUint32(utf8_cptr_t name, uint32_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a signed 64-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
int64_t PropertySet::getInt64(utf8_cptr_t name, int64_t defaultValue) const
{
    return (_setId == 0) ? defaultValue :
                           SDL_GetNumberProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of an unsigned 64-bit integer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
uint64_t PropertySet::getUint64(utf8_cptr_t name, uint64_t defaultValue) const
{
    return getIntegerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a raw pointer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
void *PropertySet::getPointer(utf8_cptr_t name, void *defaultValue) const
{
    return (_setId == 0) ? defaultValue :
                           SDL_GetPointerProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a string property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
utf8_cptr_t PropertySet::getString(utf8_cptr_t name, utf8_cptr_t defaultValue) const
{
    return (_setId == 0) ? defaultValue :
                           SDL_GetStringProperty(_setId, name, defaultValue);
}

//! @brief Gets the value of a raw pointer property.
//! @param[in] name The property name.
//! @param[in] defaultValue The value to return if the property is not defined.
//! @return The value of the property.
const void *PropertySet::getPointer(utf8_cptr_t name, const void *defaultValue) const
{
    return (_setId == 0) ? defaultValue :
                           SDL_GetPointerProperty(_setId, name,
                                                  const_cast<void *>(defaultValue));
}

//! @brief Sets the a property to a boolean value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, bool value)
{
    ensureExists();

    if (!SDL_SetBooleanProperty(_setId, name, value))
    {
        throw ApiException("SDL_SetBooleanProperty()");
    }
}

//! @brief Sets the a property to a signed 8-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, int8_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to an unsigned 8-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, uint8_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to a signed 16-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, int16_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to an unsigned 16-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, uint16_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to a signed 32-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, int32_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to an unsigned 32-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, uint32_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to a signed 64-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, int64_t value)
{
    ensureExists();

    if (!SDL_SetNumberProperty(_setId, name, value))
    {
        throw ApiException("SDL_SetNumberProperty()");
    }
}

//! @brief Sets the a property to an unsigned 64-bit integer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, uint64_t value)
{
    set(name, static_cast<int64_t>(value));
}

//! @brief Sets the a property to a 32-bit floating point value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, float value)
{
    ensureExists();

    if (!SDL_SetFloatProperty(_setId, name, value))
    {
        throw ApiException("SDL_SetFloatProperty()");
    }
}

//! @brief Sets the a property to a string value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, utf8_cptr_t value)
{
    ensureExists();

    if (!SDL_SetStringProperty(_setId, name, value))
    {
        throw ApiException("SDL_SetStringProperty()");
    }
}

//! @brief Sets the a property to a string value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, string_cref_t value)
{
    ensureExists();

    if (!SDL_SetStringProperty(_setId, name, value.getUtf8Bytes()))
    {
        throw ApiException("SDL_SetStringProperty()");
    }
}

//! @brief Sets the a property to a string value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::set(utf8_cptr_t name, const std::string_view &value)
{
    ensureExists();

    if (value.data()[value.length()] != '\0')
    {
        // The string is not null-terminated, make a temporary copy.
        std::vector<char> buffer;
        buffer.reserve(value.length() + 1);

        std::copy_n(value.begin(), value.length(), std::back_inserter(buffer));
        buffer.push_back('\0');

        set(name, buffer.data());
    }
    else if (!SDL_SetStringProperty(_setId, name, value.data()))
    {
        throw ApiException("SDL_SetStringProperty()");
    }
}

//! @brief Sets the a property to a UTF-8 string value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value encoded in wide characters.
void PropertySet::set(utf8_cptr_t name, const std::wstring_view &value)
{
    std::string buffer;
    buffer.reserve((value.length() * 110) / 100);

    Utf::appendWide(buffer, value.data(), value.length());

    set(name, buffer.c_str());
}

//! @brief Sets the a property to a pointer value.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
void PropertySet::setPointer(utf8_cptr_t name, const void *value)
{
    ensureExists();

    if (!SDL_SetPointerProperty(_setId, name, const_cast<void *>(value)))
    {
        throw ApiException("SDL_SetPointerProperty()");
    }
}

//! @brief Sets the a property to a pointer value which the property set owns.
//! @param[in] name The name of the property to set.
//! @param[in] value The new property value.
//! @param[in] deleteFn A pointer to a function which disposes of the pointer
//! once the property set is disposed of.
//! @param[in] deleterContext Optional data to pass to the deleter function.
void PropertySet::setPointer(utf8_cptr_t name, const void *value,
                             SDL_CleanupPropertyCallback deleterFn,
                             void *deleterContext /*= nullptr*/)
{
    ensureExists();

    if (!SDL_SetPointerPropertyWithCleanup(_setId, name, const_cast<void *>(value),
                                           deleterFn, deleterContext))
    {
        throw ApiException("SDL_SetPointerPropertyWithCleanup()");
    }
}

//! @brief Attempts to remove a named property from the set.
//! @param[in] name The name of the property to undefined.
//! @return A boolean value indicating whether the operation was successful.
bool PropertySet::tryClearProperty(utf8_cptr_t name)
{
    return (_setId != 0) && SDL_ClearProperty(_setId, name);
}

//! @brief Overwrites the current object with a copy of the specified
//! property set.
//! @param[in] rhs A wrapper for the property set to copy.
//! @return A reference to the current object.
PropertySet &PropertySet::operator=(const PropertySet &rhs)
{
    clone(rhs);

    return *this;
}

//! @brief Overwrites the current object by transferring the underlying
//! property set from another.
//! @param[in] rhs The object containing the property set to acquire.
//! @return A reference to the current object.
PropertySet &PropertySet::operator=(PropertySet &&rhs) noexcept
{
    if (rhs._setId != _setId)
    {
        dispose();

        std::exchange(_setId, rhs._setId);
    }

    return *this;
}

//! @brief Copies properties from another set into the one wrapped by the
//! current object, creating a copy if the current object is unbound.
//! @param[in] rhs A wrapper for the property set to copy.
//! @return A reference to the current object.
PropertySet &PropertySet::operator+=(const PropertySet &rhs)
{
    if (rhs._setId != 0)
    {
        ensureExists();

        if (!SDL_CopyProperties(rhs._setId, _setId))
        {
            throw ApiException("SDL_CopyProperties()");
        }
    }

    return *this;
}

//! @brief Gets the identifier of the underlying property set, 0 if unbound.
PropertySet::operator SDL_PropertiesID() const
{
    return _setId;
}

//! @brief Destroys any underlying property. set.
void PropertySet::dispose()
{
    SDL_PropertiesID setId = 0;

    if (std::exchange(_setId, setId) != 0)
    {
        SDL_DestroyProperties(setId);
    }
}

//! @brief Transfers ownership of a property set to this object.
//! @param[in] rhs The wrapper of the property set to transfer.
void PropertySet::assign(PropertySet &&rhs) noexcept
{
    if (rhs._setId != _setId)
    {
        dispose();

        std::exchange(_setId, rhs._setId);
    }
}

//! @brief Overwrites the current object with a copy of another
//! property set.
//! @param[in] rhs The property set to copy.
void PropertySet::clone(const PropertySet &rhs)
{
    if (_setId != rhs._setId)
    {
        dispose();

        if (rhs._setId)
        {
            ensureExists();

            SDL_CopyProperties(rhs._setId, _setId);
        }
    }
}

//! @brief Ensures the object wraps a valid property set, creating an empty
//! one if necessary.
void PropertySet::ensureExists()
{
    if (_setId == 0)
    {
        _setId = SDL_CreateProperties();

        if (_setId == 0)
        {
            throw ApiException("SDL_CreateProperties()");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// PropertySetLock Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which locks a property set for the current thread.
//! @param[in] setId The handle to the property set to lock.
PropertySetLock::PropertySetLock(SDL_PropertiesID setId) :
    _setId(0)
{
    if ((setId == 0) || SDL_LockProperties(setId))
    {
        _setId = setId;
    }
    else
    {
        throw ApiException("SDL_LockProperties()");
    }
}

//! @brief Constructs an object which locks a property set for the current thread.
//! @param[in] setId The handle to the property set to lock.
PropertySetLock::PropertySetLock(const PropertySet &properties) :
    _setId(0)
{
    SDL_PropertiesID setId = properties;

    if ((setId == 0) || SDL_LockProperties(setId))
    {
        _setId = setId;
    }
    else
    {
        throw ApiException("SDL_LockProperties()");
    }
}

//! @brief Ensures the property set was unlocked at destruction.
PropertySetLock::~PropertySetLock()
{
    SDL_PropertiesID setId = 0;

    if (std::exchange(_setId, setId))
    {
        SDL_UnlockProperties(setId);
    }
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

