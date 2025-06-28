//! @file Win32Base/CtrlArranger.cpp
//! @brief The definition of an object which arranges a number of controls in a
//! single transaction.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/BaseWindow.hpp"
#include "Ag/Win32Base/CtrlArranger.hpp"
#include "Ag/Win32Base/Ctrl.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which arranges child windows within a single
//! parent window.
//! @param[in] parentHandle The handle of the parent window.
CtrlArranger::CtrlArranger(HWND parentHandle) :
    _parentWindow(parentHandle),
    _deferredPositions(nullptr)
{
}

//! @brief Constructs an object which arranges child windows within a single
//! parent window.
//! @param[in] parent The object representing the parent window.
CtrlArranger::CtrlArranger(const BaseWindow &parent) :
    _parentWindow(parent.getHandle()),
    _deferredPositions(nullptr)
{
}

//! @brief Performs all of the previously recorded control movements as the
//! object is destroyed.
CtrlArranger::~CtrlArranger()
{
    commit();
}

//! @brief Records a new position and size of a child window.
//! @param[in] ctrlId The numeric identifier of the child window.
//! @param[in] pos The new position and size of the child window.
//! @param[in] swpFlags The flags to apply when arranging the child window.
void CtrlArranger::setPosition(uint32_t ctrlId, const RECT &pos, uint32_t swpFlags)
{
    setPosition(::GetDlgItem(_parentWindow, static_cast<int>(ctrlId)),
                pos, swpFlags);
}

//! @brief Records a new position and size of a child window.
//! @param[in] ctrl An object representing the child window.
//! @param[in] pos The new position and size of the child window.
//! @param[in] swpFlags The flags to apply when arranging the child window.
void CtrlArranger::setPosition(const Ctrl &ctrl, const RECT &pos, uint32_t swpFlags)
{
    setPosition(ctrl.getHandle(), pos, swpFlags);
}

//! @brief Records a new position and size of a child window.
//! @param[in] ctrlHandle The handle of the child window.
//! @param[in] pos The new position and size of the child window.
//! @param[in] swpFlags The flags to apply when arranging the child window.
void CtrlArranger::setPosition(HWND ctrlHandle, const RECT &pos, uint32_t swpFlags)
{
    if (ctrlHandle != nullptr)
    {
        if (_deferredPositions == nullptr)
        {
            _deferredPositions = ::BeginDeferWindowPos(64);
        }

        _deferredPositions = ::DeferWindowPos(_deferredPositions,  ctrlHandle,
                                              nullptr, pos.left, pos.top,
                                              pos.right - pos.left,
                                              pos.bottom - pos.top, swpFlags);
    }
}

//! @brief Performs all previously recorded window movements.
void CtrlArranger::commit()
{
    if (_deferredPositions != nullptr)
    {
        ::EndDeferWindowPos(_deferredPositions);
        _deferredPositions = nullptr;
    }
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
