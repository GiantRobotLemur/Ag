//! @file Ag/Win32Base/Dialog.hpp
//! @brief The declaration of an object which wraps a Win32 dialog box.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_DIALOG_HPP__
#define __AG_WIN32_BASE_DIALOG_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseWindow.hpp"
#include "Ctrl.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which wraps a Win32 dialog box.
//! @todo This class needs to be made compatible with the Dispatcher class so
//! that displaying the dialog modally still operates from the Dispatcher
//! message processing loop.
class Dialog : public BaseWindow
{
public:
    // Construction/Destruction
    Dialog(HINSTANCE moduleHandle, uint32_t dialogTemplateId);
    virtual ~Dialog();

    // Accessors
    Ctrl getCtrl(uint32_t id) const;
    HWND getCtrlHandle(uint32_t id) const;

    // Operations
    bool create(const BaseWindow *owner);
    intptr_t doModal(const BaseWindow *owner);
    void endDialog(intptr_t dialogResult);

    // Overrides
protected:
    virtual void processMessage(Message &message) override;
    virtual void onCreate(Message &message);
    virtual void onDpiScaleChange(uint32_t xDpi, uint32_t yDpi,
                                  const RECT &recommendedResize);
private:
    // Internal Functions
    static INT_PTR DialogCallback(HWND handle, UINT messageId,
                                  WPARAM wordParam, LPARAM longParam);
    void onAttach(HWND handle);
    void onDetach();

    // Internal Fields
    HINSTANCE _templateModule;
    intptr_t _modalResult;
    uint32_t _templateResourceId;
    bool _isModal;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
