//! @file Ag/Win32Base/ComTools.hpp
//! @brief The declaration of tools useful for interacting with COM objects.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_COM_TOOLS_HPP__
#define __AG_WIN32_BASE_COM_TOOLS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <type_traits>
#include <vector>
#include <utility>

#include "Ag/Core/LinearSortedMap.hpp"
#include "Ag/Core/String.hpp"
#include "Ag/Win32Base/Win32API.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief A wrapper for a typed COM interface pointer.
//! @tparam TInterface The data type of the interface to wrap.
template<typename TInterface, std::enable_if_t<std::is_base_of_v<IUnknown, TInterface>, bool> = true>
class ComPtr
{
public:
    using InterfacePtr = TInterface*;

private:
    InterfacePtr _ptr;

public:
    //! @brief Constructs a wrapper in an empty state.
    ComPtr() : _ptr(nullptr) {}

    //! @brief Constructs a wrapper to take ownership of an object reference.
    //! @param[in] ptr The pointer to the object to manage.
    ComPtr(InterfacePtr ptr) : _ptr(ptr) {}

    //! @brief Acquires an underlying object reference from another wrapper.
    //! @param[in] rhs The wrapper object to acquire the underlying interface
    //! pointer form.
    //! @note The COM object pointer is transferred, AddRef() is not called.
    ComPtr(ComPtr<TInterface>&& rhs) :
        _ptr(rhs._ptr)
    {
        rhs._ptr = nullptr;
    }

    //! @brief Copies an underlying object reference from another wrapper.
    //! @param[in] rhs The wrapper object to acquire the underlying interface
    //! pointer form.
    //! @note The COM object pointer is copied and AddRef() is called.
    ComPtr(const ComPtr<TInterface>& rhs) :
        _ptr(rhs._ptr)
    {
        if (_ptr != nullptr)
            _ptr->AddRef();
    }

    //! @brief Ensures that the wrapped interface pointer is disposed of.
    ~ComPtr()
    {
        dispose();
    }

    //! @brief Indicates if the internal interface pointer is nullptr.
    //! @retval false The wrapper points to a valid COM object.
    bool isNull() const { return _ptr == nullptr; }

    //! @brief Indicates if the internal interface pointer is valid.
    //! @retval true The wrapper points to a valid COM object.
    //! @retval false The wrapper is in an empty state.
    bool isValid() const { return _ptr != nullptr; }

    //! @brief Assigns a new interface pointer to this wrapper and
    //! treats it as a new reference. Any previously wrapped object
    //! reference is disposed of.
    //! @param[in] instance The pointer to the COM object to assign.
    //! @note AddRef() is called on @p instance, if it is valid.
    void assign(InterfacePtr instance)
    {
        if (instance != _ptr)
        {
            dispose();
            _ptr = instance;
        }

        if (_ptr != nullptr)
        {
            _ptr->AddRef();
        }
    }

    //! @brief Attaches an interface pointer to this wrapper. Any
    //! previously wrapped object reference is disposed of.
    //! @param[in] instance The pointer to the COM object to attach.
    //! @note AddRef() is NOT called on @p instance.
    void attach(InterfacePtr instance)
    {
        if (instance != _ptr)
        {
            dispose();
        }

        _ptr = instance;
    }

    //! @brief Calls Release() on any wrapped COM interface pointer, leaving
    //! the object in an empty/unbound state.
    void dispose()
    {
        IUnknown* ptr = _ptr;
        _ptr = nullptr;

        if (ptr != nullptr)
        {
            ptr->Release();
        }
    }

    //! @brief Acquires a reference to a COM object from another
    //! wrapper, disposing of any previously bound reference.
    //! @param[in] rhs The wrapper to transfer the object reference from.
    //! @return A reference to the current object.
    //! @note AddRef() is NOT called on the acquired interface pointer.
    ComPtr<TInterface>& operator=(ComPtr<TInterface>&& rhs)
    {
        if (_ptr != rhs._ptr)
        {
            dispose();

            _ptr = rhs._ptr;
            rhs._ptr = nullptr;
        }

        return *this;
    }

    //! @brief Copies a reference to a COM object.
    //! @param[in] rhs The wrapper containing the object reference to copy.
    //! @return A reference to the current object.
    //! @note AddRef() is called on the acquired interface pointer.
    ComPtr<TInterface>& operator=(const ComPtr<TInterface>& rhs)
    {
        assign(rhs._ptr);

        return *this;
    }

    //! @brief Tests whether the object is bound to an underlying COM object.
    //! @retval true The object is in a bound state.
    //! @retval false The object is in an empty state.
    operator bool() const { return _ptr != nullptr; }

    //! @brief Attempts to obtain a pointer to the underlying COM object.
    //! @return A valid COM object pointer.
    //! @throws ObjectNotBoundException If the object is in an unbound state.
    InterfacePtr operator->() const
    {
        if (_ptr == nullptr)
            throw ObjectNotBoundException("COM object", "Function call");

        return _ptr;
    }

    //! @brief Gets a pointer to the underlying COM object without checking if
    //! it is valid.
    InterfacePtr get() const { return _ptr; }

    //! @brief Resets the object to an empty state and gets a pointer to the
    //! inner interface pointer which can be set externally.
    //! @return A pointer to the inner interface pointer.
    InterfacePtr* getTargetPtr()
    {
        dispose();

        return &_ptr;
    }

    //! @brief Resets the object to an empty state and gets a pointer to the
    //! inner interface pointer which can be set externally.
    //! @return A void pointer to the inner interface pointer.
    void** getRawTargetPtr()
    {
        dispose();

        return reinterpret_cast<void**>(&_ptr);
    }

    //! @brief Resets the object to an empty state and gets a pointer to the
    //! inner interface pointer which can be set externally.
    //! @return A pointer to the inner interface pointer cast to a pointer to
    //! an IUnknown interface.
    IUnknown **getUnknownTargetPtr()
    {
        dispose();

        return reinterpret_cast<IUnknown **>(&_ptr);
    }

    //! @brief Attempts to cast a reference to a COM object to a new type via
    //! QueryInterface() and assign it to the current object. Any previous COM
    //! object reference is disposed of.
    //! @tparam U The interface type of the COM object to cast.
    //! @param[in] interfaceId A reference to the GUID identifying the type
    //! compatible with the current wrapper.
    //! @param[in] ptr The wrapper containing the interface pointer to cast.
    //! @retval true The cast was successful, the object now wraps the new
    //! interface pointer.
    //! @retval false Either @ptr was in an unbound state or the cast failed.
    template<typename U, std::enable_if_t<std::is_base_of_v<IUnknown, U>, bool> = true>
    bool tryCast(REFIID interfaceId, ComPtr<U> &ptr) const
    {
        bool canCast = false;

        if (_ptr != nullptr)
        {
            HRESULT hr = _ptr->QueryInterface(interfaceId, ptr.getRawTargetPtr());

            canCast = SUCCEEDED(hr);
        }

        return canCast;
    }
};

//! @brief A template defining a flexible array of COM object reference of
//! a uniform type.
//! @tparam T The data type of the COM objects to wrap.
template<typename T> class ComArray
{
public:
    using InterfacePtr = T*;
    using InterfaceComPtr = ComPtr<T>;

private:
    std::vector<InterfaceComPtr> _items;

public:
    //! @brief Constructs an empty array.
    ComArray() = default;

    //! @brief Creates a copy of an array of COM pointers in task memory and
    //! then disposes of that memory.
    //! @param[in] rawItems The array to copy and dispose of.
    //! @param[in] count The count of items in @p rawItems.
    ComArray(InterfacePtr* rawItems, size_t count)
    {
        assignFromTaskMem(rawItems, count);
    }

    //! @brief Ensures the COM object pointers are all properly disposed of.
    ~ComArray() = default;

    //! @brief Copies the interface pointers in an array to an internal array
    //! of COM object wrappers, then disposes of the original array.
    //! @param[in] rawItems The array to be disposed of with CoTaskMemFree().
    //! @param[in] count The count of interface pointers in @p rawItems.
    void assignFromTaskMem(InterfacePtr* rawItems, size_t count)
    {
        _items.clear();

        if ((count > 0) && (rawItems != nullptr))
        {
            _items.resize(count);

            for (size_t i = 0; i < count; ++i)
            {
                _items[i].attach(rawItems[i]);
            }

            ::CoTaskMemFree(rawItems);
        }
    }

    //! @brief Gets a pointer to the array of wrappers.
    const InterfaceComPtr* getItems() const { return _items.data(); }

    //! @brief Gets a reference to a wrapper by index.
    //! @param[in] i The zero-based index of the item to obtain.
    //! @return A reference to the indexed item.
    const InterfaceComPtr& getItem(size_t i) const { return _items.at(i); }

    //! @brief Gets the count of COM object wrappers in the array.
    size_t getCount() const { return _items.size(); }
};

//! @brief An object which can translate COM HRESULT error codes into messages.
class ComDomain
{
public:
    // Construction/Destruction
    ComDomain(const std::pair<HRESULT, std::string_view> *mappings, size_t count,
              const ComDomain *parent = nullptr);
    ~ComDomain() = default;

    // Accessors
    bool tryGetMessage(HRESULT hr, Ag::string_ref_t message) const;

    static const ComDomain &getCoreDomain();
private:
    // Internal Fields
    Ag::LinearSortedMap<HRESULT, Ag::String> _mappings;
    const ComDomain *_parent;
};

//! @brief An object which can translate a GUID into recognisable text.
class GuidDomain
{
public:
    // Construction/Destruction
    GuidDomain(const std::pair<GUID, std::string_view> *mappings, size_t count,
               const GuidDomain *parent = nullptr);
    ~GuidDomain() = default;

    // Accessors
    bool tryGetDisplay(REFIID id, Ag::string_ref_t message) const;

    static const GuidDomain &getCoreDomain();
private:
    // Internal Types
    struct GuidLess
    {
        bool operator()(const GUID &lhs, const GUID &rhs) const;
    };

    // Internal Fields
    Ag::LinearSortedMap<GUID, Ag::String, GuidLess> _mappings;
    const GuidDomain *_parent;
};

//! @brief An exception thrown when a COM function returns an unexpected error code.
class ComException : public Ag::Exception
{
public:
    ComException(const std::string_view &fnName, HRESULT hr,
                 const ComDomain &domain, IUnknown *obj = nullptr);
    virtual ~ComException() = default;
};

//! @brief An object which takes ownership of a block of memory on the default
//! OLE heap.
//! @remarks The object ensures the block is freed with CoTaskMemFree().
template<typename T>
struct ComTaskMemBlock
{
private:
    T* _ptr;
public:
    //! @brief Constructs an object in an empty state.
    ComTaskMemBlock() : _ptr(nullptr) { }

    //! @brief Takes ownership of a block of OLE memory.
    //! @param[in] ptr A pointer to the block to be managed.
    ComTaskMemBlock(T* ptr) : _ptr(ptr) { }

    //! @brief Ensures any bound block of memory is properly disposed of.
    ~ComTaskMemBlock() { dispose(); }

    // Accessors
    //! @brief Gets a pointer to the memory block, or nullptr.
    T* get() { return _ptr; }

    //! @brief Gets a read-only pointer to the memory block, or nullptr.
    const T* get() const { return _ptr; }

    //! @brief Disposes of any inner array and returns a pointer to
    //! the block, ready to be filled externally.
    T** getTarget() { dispose(); return &_ptr; }

    //! @brief Disposes of any inner array and returns a pointer to
    //! the block as a void pointer, ready to be filled externally.
    PVOID* getRawTarget() { dispose(); return &_ptr; }

    // Operations
    //! @brief Disposes of any previous pointer and takes ownership of a
    //! new one.
    void attach(T* ptr)
    {
        dispose();
        _ptr = ptr;
    }

    //! @brief Ensures any wrapped pointer is properly disposed of.
    void dispose()
    {
        PVOID ptr = std::exchange(_ptr, nullptr);

        if (ptr != nullptr)
        {
            ::CoTaskMemFree(ptr);
        }
    }
};

bool guidLessThan(REFIID lhsId, REFIID rhsId);
int guidCompare(REFIID lhsId, REFIID rhsId);
void appendGuid(std::string &buffer, REFIID iid);
Ag::String iidToString(const GuidDomain &domain, REFIID iid);

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
