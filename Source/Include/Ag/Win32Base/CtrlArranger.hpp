//! @file Ag/Win32Base/CtrlArranger.hpp
//! @brief The declaration of an object which arranges a number of controls.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_CTRL_ARRANGER_HPP__
#define __AG_WIN32_BASE_CTRL_ARRANGER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include "Win32API.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class BaseWindow;
class Ctrl;

//! @brief An object which arranges a number of controls as a single transaction.
class CtrlArranger
{
public:
    // Construction/Destruction
    CtrlArranger(HWND parentHandle);
    CtrlArranger(const BaseWindow &parent);
    ~CtrlArranger();

    // Operations
    void setPosition(uint32_t ctrlId, const RECT &pos,
                     uint32_t swpFlags = SWP_NOZORDER | SWP_NOACTIVATE);
    void setPosition(const Ctrl &ctrl, const RECT &pos,
                     uint32_t swpFlags = SWP_NOZORDER | SWP_NOACTIVATE);
    void setPosition(HWND ctrlHandle, const RECT &pos,
                     uint32_t swpFlags = SWP_NOZORDER | SWP_NOACTIVATE);

    void commit();
private:
    // Internal Fields
    HWND _parentWindow;
    HDWP _deferredPositions;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
