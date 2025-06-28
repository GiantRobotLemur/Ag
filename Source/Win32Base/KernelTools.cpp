//! @file Win32Base/KernelTools.cpp
//! @brief The definition of utilities functions and classes which interface
//! with the Windows kernel.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/KernelTools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// KernelFile Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object not attached to a kernel file handle.
KernelFile::KernelFile() :
    _handle(INVALID_HANDLE_VALUE),
    _closeOnDestroy(false)
{
}

//! @brief Ensures the file handle is closed, if required.
KernelFile::~KernelFile()
{
    if (_closeOnDestroy)
        close();
}

//! @brief Determines if the object is bound to a valid file handle.
bool KernelFile::isOpen() const { return _handle != INVALID_HANDLE_VALUE; }

//! @brief Gets the file handle the object is bound to.
HANDLE KernelFile::getHandle() const { return _handle; }

//! @brief Gets the optional path to the kernel object this object is bound to.
Ag::string_cref_t KernelFile::getPath() const { return _path; }

//! @brief Essentially replicates the isOpen() member function in operator form.
KernelFile::operator bool() const
{
    return _handle != INVALID_HANDLE_VALUE;
}

//! @brief Binds the object to a kernel file handle without taking ownership.
//! @param[in] handle The handle to passively wrap.
//! @param[in] path The optional path to the object the handle refers to.
void KernelFile::attach(HANDLE handle, Ag::string_cref_t path /*= Ag::String::Empty*/)
{
    if (handle != _handle)
    {
        ensureClosed();
    }

    _closeOnDestroy = false;

    if (_handle != INVALID_HANDLE_VALUE)
    {
        _handle = handle;
        _path = path;
    }
}

//! @brief Takes ownership of a kernel file handle, closing it on destruction.
//! @param[in] handle The handle to wrap.
//! @param[in] path The optional path to the object the handle refers to.
void KernelFile::assign(HANDLE handle, Ag::string_cref_t path /*= Ag::String::Empty*/)
{
    if (handle != _handle)
    {
        ensureClosed();
    }

    _closeOnDestroy = true;

    if (_handle != INVALID_HANDLE_VALUE)
    {
        _handle = handle;
        _path = path;
    }
}

//! @brief Creates a connection to a kernel file object, possibly creating
//! a file.
//! @param[in] access Flags specifying desired access to the opened object such
//! as GENERIC_READ and GENERIC_WRITE.
//! @param[in] shareMode Flags specifying the level of cooperative access, such
//! as FILE_SHARE_READ.
//! @param[in] creationFlags A value indicating whether a new object should be
//! created such as OPEN_EXISTING or CREATE_NEW.
//! @param[in] attribs Flags defining additional file attributes such as
//! FILE_ATTRIBUTE_NORMAL.
//! @param[out] errorCode Receives the error code captured if the underlying
//! call to CreateFileW() fails.
//! @retval true The handle was successfully opened and the object took
//! ownership of it.
//! @retval false The handle could not be opened, errorCode indicates why.
bool KernelFile::tryCreate(Ag::string_cref_t path, uint32_t access,
                           uint32_t shareMode, uint32_t creationFlags,
                           uint32_t attribs, uint32_t &errorCode)
{
    ensureClosed();

    std::vector<WCHAR> pathBuffer;
    path.appendToWideBuffer(pathBuffer);
    pathBuffer.push_back(L'\0');

    _handle = ::CreateFileW(pathBuffer.data(), access, shareMode,
                            nullptr, creationFlags, attribs, nullptr);

    if (_handle == INVALID_HANDLE_VALUE)
    {
        errorCode = ::GetLastError();

        return false;
    }
    else
    {
        _path = path;
        _closeOnDestroy = true;
        errorCode = ERROR_SUCCESS;
        return true;
    }
}

//! @brief Creates a connection to a kernel file object, possibly creating
//! a file, throwing an exception on failure.
//! @param[in] access Flags specifying desired access to the opened object such
//! as GENERIC_READ and GENERIC_WRITE.
//! @param[in] shareMode Flags specifying the level of cooperative access, such
//! as FILE_SHARE_READ.
//! @param[in] creationFlags A value indicating whether a new object should be
//! created such as OPEN_EXISTING or CREATE_NEW.
//! @param[in] attribs Flags defining additional file attributes such as
//! FILE_ATTRIBUTE_NORMAL.
//! @param[out] errorCode Receives the error code captured if the underlying
//! call to CreateFileW() fails.
//! @throws Win32Exception If the operation failed.
void KernelFile::create(Ag::string_cref_t path, uint32_t access,
                        uint32_t shareMode, uint32_t creationFlags,
                        uint32_t attribs)
{
    uint32_t error;

    if (tryCreate(path, access, shareMode, creationFlags,
                  attribs, error) == false)
    {
        std::string buffer;
        buffer.append("CreateFileW('");
        Ag::appendAgString(buffer, path);
        buffer.append("')");

        throw Ag::Win32Exception(buffer.c_str(), error);
    }
}

//! @brief Forces the handle to be closed, whether attached or assigned.
void KernelFile::close()
{
    if (_handle != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(_handle);
        _handle = INVALID_HANDLE_VALUE;
        _path = Ag::String::Empty;
    }
}

//! @brief Sends a control code directly to a specified device driver,
//! causing the corresponding device to perform the corresponding operation.
//! @param[in] op The control code for the operation.
//! @param[in] inputBuffer A pointer to the input buffer that contains the[ ]
//! data required to perform the operation.
//! @param[in] inputByteCount The size of the buffer pointed to
//! by @p inputBuffer.
//! @param[out] outputBuffer The output buffer which receives the response.
//! @retval true If the operation was successful.
//! @retval false The operation failed, but not because of an output buffer
//! which was too small.
//! @details
//! The member function calls DeviceIoControl() and if the return
//! value is ERROR_MORE_DATA or ERROR_INSUFFICIENT_BUFFER, the output
//! buffer will be extended and the call repeated.
bool KernelFile::deviceIOControl(uint32_t op, void *inputBuffer,
                                 size_t inputByteCount,
                                 ByteBlock &outputBuffer) const
{
    if (_handle == INVALID_HANDLE_VALUE)
    {
        throw ObjectNotBoundException("File", "DeviceIoControl()");
    }

    size_t bufferSize = outputBuffer.capacity();
    uint32_t errorCode = ERROR_SUCCESS;
    BOOL result = FALSE;
    bool needsMoreData = false;

    do
    {
        // Resize the buffer to it's maximum capacity without having to
        // re-allocate memory.
        if (outputBuffer.size() < bufferSize)
        {
            outputBuffer.resize(bufferSize, 0);
        }

        LPVOID outputData = outputBuffer.data();
        DWORD outputSize = static_cast<DWORD>(outputBuffer.size());
        DWORD bytesReturned = 0;

        result = ::DeviceIoControl(_handle, op, const_cast<void *>(inputBuffer),
                                   static_cast<DWORD>(inputByteCount),
                                   outputData, outputSize, &bytesReturned, nullptr);

        if (result)
        {
            // Truncate the output buffer.
            outputBuffer.resize(bytesReturned);
            errorCode = ERROR_SUCCESS;
        }
        else
        {
            errorCode = ::GetLastError();

            if ((errorCode == ERROR_MORE_DATA) || (errorCode == ERROR_INSUFFICIENT_BUFFER))
            {
                bufferSize = std::max(bufferSize << 1, Ag::toSize(256));
                needsMoreData = true;
            }
        }
    } while (needsMoreData);

    return (result != FALSE);
}

//! @brief Ensures the object is detached from the current file handle, closing
//! it if the object had ownership.
void KernelFile::ensureClosed()
{
    if (_closeOnDestroy && (_handle != INVALID_HANDLE_VALUE))
    {
        ::CloseHandle(_handle);
    }

    _handle = INVALID_HANDLE_VALUE;
    _path = Ag::String::Empty;
}

////////////////////////////////////////////////////////////////////////////////
// RuntimeLinker Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to resolve entry points from a loaded module.
//! @param[in] name The name of the module to resolve entry points from, not
//! necessarily its file path, possibly even an alias.
RuntimeLinker::RuntimeLinker(const std::string_view& name) :
    _handle(nullptr)
{
    std::wstring buffer;
    Ag::Utf::appendNative(buffer, name.data(), name.size());

    initialise(buffer.c_str());
}

//! @brief Constructs an object to resolve entry points from a loaded module.
//! @param[in] name The null-terminated name of the module to resolve entry
//! points from, not necessarily its file path, possibly even an alias.
RuntimeLinker::RuntimeLinker(const wchar_t* name) :
    _handle(nullptr)
{
    initialise(name);
}

//! @brief Determines if the module is loaded, and entry points can be resolved.
bool RuntimeLinker::isLoaded() const { return _handle != nullptr; }

//! @brief Attempts to resolve a named entry point from the module.
//! @param[in] fnName The name of the function to resolve.
//! @param[out] addr Receives the address of the entry point.
bool RuntimeLinker::tryGetEntryPoint(const char* fnName, PROC& addr) const
{
    addr = nullptr;

    if ((_handle != nullptr) && (fnName != nullptr) && (*fnName != '\0'))
    {
        addr = ::GetProcAddress(_handle, fnName);

        return addr != nullptr;
    }
    else
    {
        return false;
    }
}

//! @brief Attempts to obtain a handle to the named module.
//! @param[in] name The null-terminated name of the module to resolve entry
//! points from, not necessarily its file path, possibly even an alias.
void RuntimeLinker::initialise(const wchar_t* name)
{
    HMODULE handle = ::GetModuleHandleW(name);

    if (handle == nullptr)
    {
        // If the library wasn't already loaded, try doing so.
        handle = ::LoadLibraryW(name);
    }

    if (handle != nullptr)
    {
        _handle = handle;
        _alias = name;

        std::vector<wchar_t> buffer;
        appendModuleFilePath(_handle, buffer);

        _filePath = Ag::String(buffer.data(), buffer.size());
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Appends the full path of a module to a wide character buffer.
//! @param[in] handle The handle of the module to obtain a file path for.
//! @param[in,out] buffer The buffer to append characters to.
//! @remarks The @p buffer is not expected to be null terminated on entry and
//! the resultant buffer will not be null-terminated on return.
void appendModuleFilePath(HMODULE handle, std::vector<wchar_t>& buffer)
{
    HMODULE hModule = reinterpret_cast<HMODULE>(handle);

    size_t originalSize = buffer.size();
    size_t bufferSize = std::max(buffer.capacity(), originalSize + static_cast<size_t>(MAX_PATH));

    buffer.resize(bufferSize, L'\0');

    // Attempt to get the module file name as Unicode text into the
    // existing buffer.
    size_t length = ::GetModuleFileNameW(hModule, buffer.data() + originalSize,
                                         static_cast<DWORD>(buffer.size() - originalSize));

    if (length > 0)
    {
        while (length == buffer.size())
        {
            // The buffer wasn't large enough. Resize and try again.
            buffer.resize(buffer.size() * 2, L'\0');

            length = ::GetModuleFileNameW(hModule, buffer.data() + originalSize,
                                          static_cast<DWORD>(buffer.size() - originalSize));
        }

        // Truncate the buffer to the required size.
        buffer.resize(length + originalSize);
    }
    else
    {
        // The initial attempt failed, don't try again.
        throw Win32Exception("GetModuleFileName()", ::GetLastError());
    }
}

//! @brief Appends the full path of a module to a wide string.
//! @param[in] handle The handle of the module to obtain a file path for.
//! @param[in,out] buffer The string to append characters to.
void appendModuleFilePath(HMODULE handle, std::wstring& buffer)
{
    std::vector<wchar_t> characterBuffer;

    appendModuleFilePath(handle, characterBuffer);
    buffer.append(characterBuffer.data(), characterBuffer.size());
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
