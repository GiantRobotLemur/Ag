//! @file Core/Win32API.cpp
//! @brief The definition of some helper functions which assist the user of
//! the Win32 API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////

#include "Win32API.hpp"
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Core/Utf.hpp"

#include <cwchar>

#include <memory>
#include <vector>

namespace Ag {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Attempts to convert an HRESULT into a Win32 error code.
//! @param[in] hr The HRESULT value to attempt to convert.
//! @param[out] errorCode Receives the converted error code, if successful.
//! @retval true The conversion was successful, @p errorCode was updated.
//! @retval false The HRESULT did not have an equivalent Win32 error code.
bool tryConvertHResultToWin32Error(HRESULT hr, DWORD &errorCode)
{
    // Inspired by: https://stackoverflow.com/questions/22233527/how-to-convert-hresult-into-an-error-description
    bool isConverted = true;

    if ((hr & 0xFFFF0000) == MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, 0))
    {
        errorCode = HRESULT_CODE(hr);
    }
    else if (hr == S_OK)
    {
        errorCode = ERROR_SUCCESS;
    }
    else
    {
        // Not a Win32 HRESULT so return failure.
        errorCode = 0;
        isConverted = false;
    }

    return isConverted;
}

//! @brief Attempts to get the full path to a module file name.
//! @param[in] handle The handle of the module to obtain a file name for.
//! @param[out] buffer Receives the path in wide characters.
//! @throws Win32Exception If the module was invalid.
void getModuleFileName(uintptr_t handle, std::vector<wchar_t> &buffer)
{
    HMODULE hModule = reinterpret_cast<HMODULE>(handle);

    buffer.resize(256);

    // Attempt to get the module file name as Unicode text into the
    // existing buffer.
    size_t length = ::GetModuleFileNameW(hModule, buffer.data(),
                                         static_cast<DWORD>(buffer.size()));
    if (length > 0)
    {
        while (length == buffer.size())
        {
            // The buffer wasn't large enough. Resize and try again.
            buffer.resize(buffer.size() * 2, L'\0');

            length = ::GetModuleFileNameW(hModule, buffer.data(),
                                          static_cast<DWORD>(buffer.size()));
        }

        // Truncate the buffer to the required size.
        buffer.resize(length);
    }
    else
    {
        // The initial attempt failed, don't try again.
        throw Win32Exception("GetModuleFileName()", ::GetLastError());
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the absolute path to the currently running executable.
String getProgramFileName()
{
    std::vector<wchar_t> wideBuffer;

    getModuleFileName(static_cast<uintptr_t>(0), wideBuffer);

    return String(wideBuffer.data(), wideBuffer.size());
}

//! @brief Gets the path an file name of a module loaded into the current process.
//! @param[in] moduleHandle The handle of the loaded module.
//! @return The full path to the module and its file name.
String getModuleFileName(uintptr_t moduleHandle)
{
    std::vector<wchar_t> wideBuffer;

    getModuleFileName(moduleHandle, wideBuffer);

    return String(wideBuffer.data(), wideBuffer.size());
}

//! @brief Gets the path an directory containing a module loaded into the
//! current process.
//! @param[in] moduleHandle The handle of the loaded module.
//! @return The full path to the module minus its file name.
String getModuleDirectory(uintptr_t moduleHandle)
{
    std::vector<wchar_t> wideBuffer;

    getModuleFileName(moduleHandle, wideBuffer);

    size_t length;
    for (length = wideBuffer.size(); length > 0; --length)
    {
        wchar_t ch = wideBuffer[length - 1];

        if ((ch == L'\\') || (ch == '/'))
        {
            // We've found the last path element separator.
            --length;
            break;
        }
    }

    return String(wideBuffer.data(), length);
}

//! @brief Gets the full path of the current working directory of the
//! current process.
String getWorkingDirectory()
{
    uint32_t requiredSize = ::GetCurrentDirectoryW(0, nullptr);

    if (requiredSize > 0)
    {
        std::vector<wchar_t> buffer;
        buffer.resize(requiredSize);

        uint32_t charsWritten = ::GetCurrentDirectoryW(requiredSize, buffer.data());

        if (charsWritten > 0)
        {
            return String(buffer.data(), charsWritten);
        }
    }
    else
    {
        throw Win32Exception("GetCurrentDirectory()", ::GetLastError());
    }

    return String::Empty;
}

//! @brief Gets the full path of the directory used to store temporary files.
String getTempDirectory()
{
    std::vector<wchar_t> buffer;
    buffer.resize(MAX_PATH, L'\0');

    DWORD bufferSize = static_cast<DWORD>(buffer.size());
    DWORD result = ::GetTempPath2W(bufferSize, buffer.data());

    if (result == 0)
    {
        throw Win32Exception("GetTempPath2()", ::GetLastError());
    }
    else if (result > bufferSize)
    {
        buffer.resize(result + 1, L'\0');
        bufferSize = result + 1;

        result = ::GetTempPath2W(bufferSize, buffer.data());
    }

    return String(buffer.data(), static_cast<size_t>(result));
}

//! @brief Gets the profile directory of the current user.
String getHomeDirectory()
{
    wchar_t *profileDir = nullptr;
    size_t profileDirLength = 0;
    auto error = _wdupenv_s(&profileDir, &profileDirLength, L"USERPROFILE");

    String profilePath;

    if ((error == 0) && (profileDir != nullptr) && (profileDirLength > 0))
    {
        profilePath = String(profileDir, profileDirLength - 1);
    }

    if (profileDir != nullptr)
    {
        free(profileDir);
        profileDir = nullptr;
    }

    return profilePath;
}

//! @brief Queries the path to a known folder location.
//! @param[in] id The identifier of the known folder, such as FOLDERID_Documents.
//! @param[in] forceCreate True to attempt to create the folder if it does
//! not exist.
//! @returns The path to the specified folder, if it has one.
//! @throws Win32Exception Thrown if the folder path cannot be obtained, or
//! if @p forceCreate is true, but the folder cannot be created.
String getKnownDirectory(const KNOWNFOLDERID &id, bool forceCreate /*= false*/)
{
    PWSTR buffer = nullptr;
    DWORD flags = forceCreate ? KF_FLAG_CREATE : KF_FLAG_DEFAULT;
    DWORD errorCode;

    HRESULT hr = ::SHGetKnownFolderPath(id, flags, nullptr, &buffer);

    if (SUCCEEDED(hr))
    {
        // Ensure the buffer is freed no matter what else happens.
        AtScopeExit1 freeBuffer(CoTaskMemFree, buffer);

        return String(buffer);
    }
    else if (tryConvertHResultToWin32Error(hr, errorCode) == false)
    {
        // Assign a misc error code.
        errorCode = ERROR_BAD_COMMAND;
    }

    throw Win32Exception("SHGetKnownFolderPath()", errorCode);
}

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

