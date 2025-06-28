//! @file Ag/Sdl3Tools/PropertySet.hpp
//! @brief The declaration of an object wrapping the SDL_PropertiesID handle.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_PROPERTY_SET_HPP__
#define __AG_SDL3_TOOLS_PROPERTY_SET_HPP__

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object wrapping the SDL_PropertiesID handle.
class PropertySet
{
public:
    // Construction/Destruction
    PropertySet();
    PropertySet(const PropertySet &rhs);
    PropertySet(PropertySet &&rhs) noexcept;
    PropertySet(SDL_PropertiesID propertySetID);
    ~PropertySet();

    // Accessors
    bool getBoolean(utf8_cptr_t name, bool defaultValue) const;
    float getFloat(utf8_cptr_t name, float defaultValue) const;
    int8_t getInt8(utf8_cptr_t name, int8_t defaultValue) const;
    uint8_t getUint8(utf8_cptr_t name, uint8_t defaultValue) const;
    int16_t getInt16(utf8_cptr_t name, int16_t defaultValue) const;
    uint16_t getUint16(utf8_cptr_t name, uint16_t defaultValue) const;
    int32_t getInt32(utf8_cptr_t name, int32_t defaultValue) const;
    uint32_t getUint32(utf8_cptr_t name, uint32_t defaultValue) const;
    int64_t getInt64(utf8_cptr_t name, int64_t defaultValue) const;
    uint64_t getUint64(utf8_cptr_t name, uint64_t defaultValue) const;
    void *getPointer(utf8_cptr_t name, void *defaultValue) const;
    utf8_cptr_t getString(utf8_cptr_t name, utf8_cptr_t defaultValue) const;
    const void *getPointer(utf8_cptr_t name, const void *defaultValue) const;

    //! @brief Gets the value of a typed pointer property.
    //! @tparam T The data type of the pointer.
    //! @param[in] name The name of the property to retrieve.
    //! @param[in] defaultValue The default value to return if the property is
    //! not defined.
    //! @return The value of the property.
    template<typename T>
    T *getTypedPointer(utf8_cptr_t name, T *defaultValue) const
    {
        return static_cast<T *>(getPointer(name, defaultValue));
    }

    //! @brief Gets the value of a typed const pointer property.
    //! @tparam T The data type of the pointer.
    //! @param[in] name The name of the property to retrieve.
    //! @param[in] defaultValue The default value to return if the property is
    //! not defined.
    //! @return The value of the property.
    template<typename T>
    const T *getTypedPointer(utf8_cptr_t name, const T *defaultValue) const
    {
        return static_cast<T *>(getPointer(name, defaultValue));
    }

    void set(utf8_cptr_t name, bool value);
    void set(utf8_cptr_t name, int8_t value);
    void set(utf8_cptr_t name, uint8_t value);
    void set(utf8_cptr_t name, int16_t value);
    void set(utf8_cptr_t name, uint16_t value);
    void set(utf8_cptr_t name, int32_t value);
    void set(utf8_cptr_t name, uint32_t value);
    void set(utf8_cptr_t name, int64_t value);
    void set(utf8_cptr_t name, uint64_t value);
    void set(utf8_cptr_t name, float value);
    void set(utf8_cptr_t name, utf8_cptr_t value);
    void set(utf8_cptr_t name, string_cref_t value);
    void set(utf8_cptr_t name, const std::string_view &value);
    void set(utf8_cptr_t name, const std::wstring_view &value);

    void setPointer(utf8_cptr_t name, const void *value);
    void setPointer(utf8_cptr_t name, const void *value,
                    SDL_CleanupPropertyCallback deleterFn,
                    void *deleterContext = nullptr);

    template<typename T, typename U>
    void setTypedPointer(utf8_cptr_t name, const T *value,
                         void (SDLCALL *deleterFn)(U *userdata, T *value),
                         U *deleterContext = nullptr)
    {
        setPointer(name, value,
                   reinterpret_cast<SDL_CleanupPropertyCallback>(deleterFn),
                   deleterContext);
    }

    // Operations
    bool tryClearProperty(const char *name);
    PropertySet &operator=(const PropertySet &rhs);
    PropertySet &operator=(PropertySet &&rhs) noexcept;
    PropertySet &operator+=(const PropertySet &rhs);
    operator SDL_PropertiesID() const;
    void dispose();
private:
    // Internal Types

    // Internal Functions
    void assign(PropertySet &&rhs) noexcept;
    void clone(const PropertySet &rhs);
    void ensureExists();

    // Internal Fields
    SDL_PropertiesID _setId;
};

//! @brief An object which locks a property set for its lifetime.
class PropertySetLock
{
public:
    // Construction/Destruction
    PropertySetLock(SDL_PropertiesID setId);
    PropertySetLock(const PropertySet &properties);
    ~PropertySetLock();

private:
    // Internal Fields
    SDL_PropertiesID _setId;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
