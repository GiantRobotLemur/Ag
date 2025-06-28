//! @file WriteGlyphGeometry/Helpers.cpp
//! @brief The definition of various stand-alone utility functions.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Helpers.hpp"

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Resolves a relative path using the current working directory.
//! @param[in] path The relative path to resolve.
//! @returns An absolute path referencing the same file system object.
std::wstring toFullPath(const std::wstring &path)
{
    std::wstring fullPath;

    if (path.empty() == false)
    {
        wchar_t *fullPathText = _wfullpath(nullptr, path.c_str(), 0);

        if (fullPathText == nullptr)
        {
            fullPath = path;
        }
        else
        {
            fullPath = fullPathText;
            free(fullPathText);
            fullPathText = nullptr;
        }
    }

    return fullPath;
}

//! @brief Creates a new file path with a new extension, replacing any previous
//! extension.
//! @param[in] fileName The original path to copy and alter.
//! @param[in] newExt The new extension to apply, leading period characters will
//! be ignored.
//! @return A new file name with the new extension applied.
std::wstring changeFileExt(const std::wstring_view &fileName,
                           const std::wstring_view &newExt)
{
    std::wstring newPath;
    newPath.reserve(fileName.length() + newExt.length() + 1);

    auto pos = fileName.rfind(L'.');
    auto extStart = newExt.find_first_not_of(L'.');

    if (pos < fileName.length())
    {
        // The original file name has an extension.
        // Copy characters up to and including the period.
        newPath.append(fileName, 0, pos + 1);

        // Copy the extension, ignoring any leading period.
        newPath.append(newExt, extStart);
    }
    else
    {
        // The original path has no extension.
        newPath.append(fileName);
        newPath.push_back(L'.');
        newPath.append(newExt, extStart);
    }

    return newPath;
}

//! @brief Extracts a file name from the end of a file path string.
//! @param[in] filePath The file path to analyse.
//! @return A portion of the file path representing just the file name.
std::wstring_view getFileName(const std::wstring_view &filePath)
{
    size_t pos = filePath.find_last_of(L"\\/");

    return (pos < filePath.length()) ? filePath.substr(pos + 1) : filePath;
}

//! @brief Gets the error message associated with a Win32 error code.
//! @param[in] errorCode The Win32 error code to interpret.
//! @return A string expressing the error as text or an empty string.
std::wstring getWin32ErrorMessage(uint32_t errorCode)
{
    LPWSTR messageBuffer = nullptr;

    uint32_t length = ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                       FORMAT_MESSAGE_FROM_SYSTEM |
                                       FORMAT_MESSAGE_IGNORE_INSERTS,
                                       nullptr, errorCode,
                                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                       reinterpret_cast<LPWSTR>(&messageBuffer),
                                       0, nullptr);

    std::wstring message;

    if (length > 0)
    {
        message.assign(messageBuffer, length);
        ::LocalFree(messageBuffer);
    }

    return message;
}

//! @brief Appends a message to an error string.
//! @param[in,out] error The text to append to.
//! @param[in] errorCode The error code, if ERROR_SUCCESS, no error occurred.
//! @retval true An error message was successfully found and appended.
//! @retval false There was no error, or a message could not be found.
bool appendOptionalErrorMessage(std::wstring &error, uint32_t errorCode)
{
    if (errorCode == ERROR_SUCCESS)
    {
        // No error.
        error.push_back(L'.');
        return false;
    }

    LPWSTR messageBuffer = nullptr;

    uint32_t length = ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                       FORMAT_MESSAGE_FROM_SYSTEM |
                                       FORMAT_MESSAGE_IGNORE_INSERTS,
                                       nullptr, errorCode,
                                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                       reinterpret_cast<LPWSTR>(&messageBuffer),
                                       0, nullptr);

    if (length > 0)
    {
        error.reserve(error.length() + length + 2);
        error.push_back(L':');
        error.push_back(L' ');
        error.append(messageBuffer, static_cast<size_t>(length));

        return true;
    }
    else
    {
        error.push_back(L'.');
        return false;
    }
}

//! @brief Gets the message associated with a runtime library error code.
//! @param[in] errorCode The error code to interpret.
//! @return The error message associated with @p errorCode, or an empty string
//! if not message could be mapped.
std::wstring getCRTErrorMessage(errno_t errorCode)
{
    std::vector<wchar_t> buffer;
    size_t requiredSize = 32;

    do
    {
        buffer.resize(requiredSize, L'\0');

        if (_wcserror_s(buffer.data(), buffer.size(), errorCode) != 0)
        {
            // No error message can be retrieved, return an empty string.
            return { };
        }

        requiredSize *= 2;
    } while (buffer[buffer.size() - 2] == L'\0');

    return std::wstring(buffer.data());
}

void appendOptionalCRTErrorMessage(std::wstring &error, errno_t errorCode)
{
    auto message = getCRTErrorMessage(errorCode);

    if (message.empty())
    {
        error.push_back(L'.');
    }
    else
    {
        error.push_back(L':');
        error.push_back(L' ');
        error.append(message);
    }
}

////////////////////////////////////////////////////////////////////////////////

