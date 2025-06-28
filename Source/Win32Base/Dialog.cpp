//! @file Win32Base/Dialog.cpp
//! @brief The definition of an object which wraps a Win32 dialog box.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/Win32API.hpp"

#include <algorithm>

#include "InternalTools.hpp"

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/Dialog.hpp"
#include "Ag/Win32Base/GuiApp.hpp"
#include "Ag/Win32Base/Message.hpp"
#include "Ag/Win32Base/Tools.hpp"

namespace Ag {
namespace Win32 {

namespace {


////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
bool isDialogBound(uintptr_t context)
{
    Dialog *dialog = reinterpret_cast<Dialog *>(context);

    return (dialog != nullptr) && dialog->isBound();
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Dialog Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to wrap a window created from a dialog template.
//! @param[in] moduleHandle The handle of the module containing the template.
//! @param[in] dialogTemplateId The numeric identifier of the dialog template.
Dialog::Dialog(HINSTANCE moduleHandle, uint32_t dialogTemplateId) :
    _templateModule(moduleHandle),
    _modalResult(0),
    _templateResourceId(dialogTemplateId),
    _isModal(false)
{
}

//! @brief Disposes of the object, ensuring any underlying dialog is properly
//! destroyed first.
Dialog::~Dialog()
{
    if (isBound())
    {
        // Ensure any running dialog is destroyed with this object.
        destroy();
    }
}

//! @brief Gets an object wrapping a child window.
//! @param[in] id The numeric identifier of the child window.
//! @return An object either wrapping the child window or unbound.
Ctrl Dialog::getCtrl(uint32_t id) const
{
    return Ctrl(getCtrlHandle(id));
}

//! @brief Gets the handle to a child window.
//! @param[in] id The numeric identifier of the child window.
//! @return The handle to the child window or nullptr.
HWND Dialog::getCtrlHandle(uint32_t id) const
{
    return ::GetDlgItem(getHandle(), static_cast<int>(id));
}

//! @brief Creates a modeless dialog and binds the current object to it.
//! @param[in] owner The optional window to be assigned as the owner.
//! @return A boolean value indicating whether the dialog was successfully
//! created.
//! @note The dialog may not be initially visible. It should be closed or
//! destroyed in the normal manner.
bool Dialog::create(const BaseWindow *owner)
{
    if (isBound())
        return false;

    // Calculate the proper window owner.
    HWND ownerHandle = nullptr;

    if ((owner != nullptr) && owner->isBound())
    {
        ownerHandle = owner->getHandle();
    }
    else
    {
        ownerHandle = ::GetDesktopWindow();
    }

    // Create a modeless dialog and bind it to the current object.
    HWND handle = ::CreateDialogParamW(_templateModule,
                                       makeResourceText(_templateResourceId),
                                       ownerHandle, DialogCallback,
                                       reinterpret_cast<LPARAM>(this));

    if (::IsWindow(handle) != FALSE)
    {
        ::ShowWindow(handle, SW_SHOW);
        ::UpdateWindow(handle);
        return true;
    }
    else
    {
        return false;
    }
}

//! @brief Creates a modal dialog which blocks input the owner window until
//! closed.
//! @param[in] owner The optional window which will own the dialog.
//! @return The result of dialog processed, perhaps IDOK, IDCANCEL or the like.
//! The member function will return IDABORT on error.
//! @note The function does not return until the dialog has been closed by
//! an internal call to endDialog().
intptr_t Dialog::doModal(const BaseWindow *owner)
{
    if (isBound())
    {
        // The object is already bound to a running dialog.
        return IDABORT;
    }

    _modalResult = IDCANCEL;

    // Figure out the effective owner of the dialog.
    HWND ownerHandle = nullptr;

    if ((owner != nullptr) && owner->isBound())
    {
        ownerHandle = owner->getHandle();
    }
    else
    {
        ownerHandle = ::GetDesktopWindow();
    }

    // Create a modeless dialog and bind it to the current object.
    HWND handle = ::CreateDialogParamW(_templateModule,
                                       makeResourceText(_templateResourceId),
                                       ownerHandle, DialogCallback,
                                       reinterpret_cast<LPARAM>(this));

    if (::IsWindow(handle))
    {
        // Ensure the dialog appears to be running modally.
        Modaliser makeModal(ownerHandle, handle, &_isModal);

        // Create a local dispatcher to run the dialog.
        Dispatcher messagePump;

        messagePump.execConditional(isDialogBound,
                                   reinterpret_cast<uintptr_t>(this));
    }

    return _modalResult;
}

//! @brief Closes a modal dialog returning a specified result to the caller.
//! @param[in] dialogResult The result to return to the caller.
void Dialog::endDialog(intptr_t dialogResult)
{
    if (isBound() && _isModal)
    {
        _modalResult = dialogResult;
        destroy();
    }
}

//! @brief Performs default dialog message processing.
//! @param[in] message The message to process.
void Dialog::processMessage(Message &message)
{
    if (message.getMessageId() == WM_DPICHANGED)
    {
        PRECT recommendedResize = nullptr;

        if (message.tryGetLongParamPtr(recommendedResize))
        {
            onDpiScaleChange(message.getLowWordParameter(),
                             message.getHighWordParameter(),
                             *recommendedResize);
            message.setHandled();
        }
    }

    BaseWindow::processMessage(message);
}

//! @brief Can be overriden by derived classes to perform specific processing
//! when the WM_CREATE/WM_INITDIALOG message is processed.
//! @param[in] message Details of the message to process and the result of
//! processing it.
//! @note The base class implementation does nothing.
void Dialog::onCreate(Message &/*message*/)
{
}

//! @brief Called in response to the WM_DPICHANGED message.
//! @param[in] xDpi The new count of pixels per horizontal inch.
//! @param[in] yDpi The new count of pixels per vertical inch.
//! @param[in] recommendedResize The position and size of the window
//! adjusted for the new DPI scale.
//! @note The base implementation resizes the window to the recommended
//! rectangle.
void Dialog::onDpiScaleChange(uint32_t /* xDpi */, uint32_t /* yDpi */,
                              const RECT &recommendedResize)
{
    ::SetWindowPos(getHandle(), nullptr, recommendedResize.left,
                   recommendedResize.top,
                   recommendedResize.right - recommendedResize.left,
                   recommendedResize.bottom - recommendedResize.top,
                   SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOZORDER);
}

//! @brief The Win32 dialog message processing callback function.
//! @param[in] handle The handle of the dialog receiving the message.
//! @param[in] messageId The identifier of the message.
//! @param[in] wordParam The word message parameter.
//! @param[in] longParam The long message parameter.
//! @return TRUE if the message was processed, otherwise FALSE.
INT_PTR Dialog::DialogCallback(HWND handle, UINT messageId,
                               WPARAM wordParam, LPARAM longParam)
{
    Dialog *instance = nullptr;

    Message message(handle, messageId, wordParam, longParam);

    if ((messageId == WM_INITDIALOG) && message.tryGetLongParamPtr(instance))
    {
        instance->onAttach(handle);
        instance->onCreate(message);
    }
    else
    {
        // Get the Dialog object previously bound to the window.
        instance = reinterpret_cast<Dialog *>(::GetWindowLongPtrW(handle, DWLP_USER));
    }

    if (instance != nullptr)
    {
        // Perform message processing via the object.
        instance->processMessage(message);
    }

    if ((messageId == WM_DESTROY) && (instance != nullptr))
    {
        // Unbind the object from the dialog.
        instance->onDetach();
    }

    intptr_t result;

    if (message.tryGetResult(result))
    {
        // NOTE: These IDs are already in sorted order.
        static const uint32_t directReturnMessages[] = {
            WM_CTLCOLORMSGBOX,
            WM_CTLCOLOREDIT,
            WM_CTLCOLORLISTBOX,
            WM_CTLCOLORBTN,
            WM_CTLCOLORDLG,
            WM_CTLCOLORSCROLLBAR,
            WM_CTLCOLORSTATIC };

        if (std::binary_search(directReturnMessages,
                               directReturnMessages + std::size(directReturnMessages),
                               messageId))
        {
            // Return the message result directly.
            return result;
        }
        else
        {
            // Set the result as a window property.
            ::SetWindowLongPtrW(handle, DWLP_MSGRESULT, result);

            return TRUE;
        }
    }
    else if ((instance != nullptr) &&
             (messageId == WM_CLOSE) &&
             instance->_isModal)
    {
        instance->endDialog(IDCANCEL);
    }

    return FALSE;
}

//! @brief Performs operations when the object is first bound to a dialog window.
//! @param[in] handle The handle of the window the object is to bind to.
void Dialog::onAttach(HWND handle)
{
    attach(handle);

    // Bind the handle to the object.
    ::SetWindowLongPtrW(handle, DWLP_USER, reinterpret_cast<LPARAM>(this));

    // Setup dialog message processing within the dispatcher.
    if (GuiApp *app = dynamic_cast<GuiApp *>(Ag::App::get()))
    {
        app->getMainThreadDispatcher().addDialogWindow(handle);

        // Set the dialog icons, if possible.
        if (app->getSmallAppIcon() != nullptr)
        {
            setIcon(app->getSmallAppIcon(), ICON_SMALL);
        }

        if (app->getAppIcon() != nullptr)
        {
            setIcon(app->getAppIcon(), ICON_BIG);
        }
    }
}

//! @brief Performs operations when the object needs to be unbound from a
//! dialog window.
void Dialog::onDetach()
{
    // Remove dialog message processing from the dispatcher.
    if (GuiApp *app = dynamic_cast<GuiApp *>(Ag::App::get()))
    {
        app->getMainThreadDispatcher().removeDialogWindow(getHandle());
    }

    // Bind the handle to the object.
    ::SetWindowLongPtrW(getHandle(), DWLP_USER, 0);

    attach(nullptr);
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
