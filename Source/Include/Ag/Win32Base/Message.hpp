//! @file Ag/Win32Base/Message.hpp
//! @brief The declaration of an object representing a Win32 thread message.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_MESSAGE_HPP__
#define __AG_WIN32_BASE_MESSAGE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <optional>

#include "Win32API.hpp"
#include "Tools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing a Win32 thread message.
class Message
{
public:
    // Construction/Destruction
    Message();
    Message(HWND windowHandle, uint32_t messageId, uintptr_t wParam, intptr_t lParam);
    Message(const MSG &message);

    // Accessors
    HWND getWindowHandle() const;
    uint32_t getMessageId() const;
    uintptr_t getWordParam() const;
    intptr_t getLongParam() const;
    bool isHandled() const;
    bool tryGetResult(intptr_t &result) const;
    void setResult(intptr_t result);

    //! @brief Attempts to cast the word parameter to a typed pointer.
    //! @tparam The data type of the pointer to obtain.
    //! @param[out] ptr Receives the word parameter as a pointer.
    //! @retval true The word parameter could be a valid pointer.
    //! @retval false The word parameter value did not constitute a valid pointer.
    template<typename T> bool tryGetWordParamPtr(T *&ptr) const
    {
        bool hasPtr = false;

        if (isValidAddress(_wordParameter.WordParam))
        {
            ptr = static_cast<T *>(_wordParameter.Pointer);
            hasPtr = true;
        }
        else
        {
            ptr = nullptr;
        }

        return hasPtr;
    }

    //! @brief Attempts to cast the long parameter to a typed pointer.
    //! @tparam The data type of the pointer to obtain.
    //! @param[out] ptr Receives the long parameter as a pointer.
    //! @retval true The long parameter could be a valid pointer.
    //! @retval false The long parameter value did not constitute a valid pointer.
    template<typename T> bool tryGetLongParamPtr(T *&ptr) const
    {
        bool hasPtr = false;

        if (isValidAddress(_longParameter.WordParam))
        {
            ptr = static_cast<T *>(_longParameter.Pointer);
            hasPtr = true;
        }
        else
        {
            ptr = nullptr;
        }

        return hasPtr;
    }

    uint32_t getLowWordParameter() const;
    uint32_t getHighWordParameter() const;
    POINT getWordParameterPoint() const;
    SIZE getWordParameterSize() const;
    uint32_t getLowLongParameter() const;
    uint32_t getHighLongParameter() const;
    POINT getLongParameterPoint() const;
    SIZE getLongParameterSize() const;

    // Operations
    void setHandled();
private:
    // Internal Types
    union Parameter
    {
        uintptr_t WordParam;
        intptr_t LongParam;
        void *Pointer;
        uint16_t Words[2];
        int16_t Deltas[2];

        Parameter(uintptr_t value) :
            WordParam(value)
        {
        }
    };

    // Internal Fields
    HWND _windowHandle;
    Parameter _wordParameter;
    Parameter _longParameter;
    std::optional<intptr_t> _messageResult;
    uint32_t _messageId;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
