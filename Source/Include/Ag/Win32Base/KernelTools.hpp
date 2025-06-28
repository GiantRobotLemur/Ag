//! @file Ag/Win32Base/KernelTools.hpp
//! @brief The declaration of utilities functions and classes which interface
//! with the Windows kernel.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_KERNEL_TOOLS_HPP__
#define __AG_WIN32_BASE_KERNEL_TOOLS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

#include "Ag/Core/String.hpp"
#include "Ag/Win32Base/Win32API.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An interface to an open Win32 file handle.
class KernelFile
{
public:
    // Construction/Destruction
    KernelFile();
    ~KernelFile();

    // Accessors
    bool isOpen() const;
    HANDLE getHandle() const;
    Ag::string_cref_t getPath() const;

    // Operations
    operator bool () const;
    void attach(HANDLE handle, Ag::string_cref_t path = Ag::String::Empty);
    void assign(HANDLE handle, Ag::string_cref_t path = Ag::String::Empty);
    bool tryCreate(Ag::string_cref_t path, uint32_t access, uint32_t shareMode,
                   uint32_t creationFlags, uint32_t attribs, uint32_t &errorCode);
    void create(Ag::string_cref_t path, uint32_t access, uint32_t shareMode,
                uint32_t creationFlags, uint32_t attribs);
    void close();

    bool deviceIOControl(uint32_t op, void *inputBuffer, size_t inputByteCount,
                         ByteBlock &outputBuffer) const;
private:
    // Internal Functions
    void ensureClosed();

    // Internal Fields
    Ag::String _path;
    HANDLE _handle;
    bool _closeOnDestroy;
};

//! @brief An object which attempts to find entry points in a dynamically
//! loaded module at runtime.
class RuntimeLinker
{
public:
    // Construction/Destruction
    RuntimeLinker(const std::string_view& name);
    RuntimeLinker(const wchar_t* name);
    ~RuntimeLinker() = default;

    // Accessors
    bool isLoaded() const;

    // Operations
    //! @brief Attempts to obtain a typed entry point from the loaded module.
    //! @tparam T The pointer to function type of the entry point to obtain.
    //! @param[in] fnName The name of the function to resolve.
    //! @param[out] fnAddr Receives the typed address of the entry point.
    template<typename T>
    bool tryLink(const char* fnName, T& fnAddr) const
    {
        PROC rawEntryPoint = nullptr;

        if (tryGetEntryPoint(fnName, rawEntryPoint))
        {
            fnAddr = reinterpret_cast<T>(rawEntryPoint);

            return true;
        }
        else
        {
            return false;
        }
    }

private:
    // Internal Functions
    bool tryGetEntryPoint(const char* fnName, PROC& addr) const;
    void initialise(const wchar_t* name);

    // Internal Fields
    HMODULE _handle;
    Ag::String _alias;
    Ag::String _filePath;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
void appendModuleFilePath(HMODULE handle, std::vector<wchar_t>& buffer);
void appendModuleFilePath(HMODULE handle, std::wstring& buffer);

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
