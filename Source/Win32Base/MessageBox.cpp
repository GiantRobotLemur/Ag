//! @file Win32Base/MessageBox.cpp
//! @brief The definition of a class which allows modal message box
//! functionality to be properly integrated with the thread Dispatcher object.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#define WIN32_MEAN_AND_LEAN
#define UNICODE
#define NOMINMAX          // Macros min(a,b) and max(a,b)

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>

#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/Ctrl.hpp"
#include "Ag/Win32Base/CustomWindow.hpp"
#include "Ag/Win32Base/DeviceContext.hpp"
#include "Ag/Win32Base/Dispatcher.hpp"
#include "Ag/Win32Base/GuiApp.hpp"
#include "Ag/Win32Base/MessageMap.hpp"
#include "Ag/Win32Base/MessageBox.hpp"
#include "Ag/Win32Base/Tools.hpp"

#include "InternalTools.hpp"

namespace Ag {
namespace Win32 {
namespace MsgBox {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
namespace {

struct ButtonInfo
{
    RectD Placement;
    Ag::String Text;
    uint32_t CommandID;
    bool IsDefault;

    ButtonInfo(Ag::utf8_cptr_t text, uint32_t commandID) :
        Placement(0, 0, 75, 23),
        Text(text),
        CommandID(commandID),
        IsDefault(false)
    {
    }
};

class MessageDialog : public CustomWindow
{
private:
    // Internal Fields
    HFONT _textFont;
    HICON _image;
    PointI _imageOrigin;
    LegacyRect _textRect;
    std::wstring _messageText;
    Button _result;
public:
    // Construction/Destruction
    MessageDialog() :
        _textFont(nullptr),
        _image(nullptr),
        _result(None)
    {
    }

    bool createInstance(HWND ownerHandle,
                        Ag::string_cref_t message, Ag::string_cref_t title,
                        uint32_t buttons, Icon icon,
                        Button defaultButton)
    {
        constexpr uint32_t Style = WS_CAPTION | WS_BORDER | WS_SYSMENU;
        constexpr uint32_t ExStyle = WS_EX_WINDOWEDGE;
        bool isOK = false;

        _messageText = message.toWide();
        bool transferIcons = true;

        if (ownerHandle == nullptr)
        {
            ownerHandle = ::GetDesktopWindow();
            transferIcons = false;
        }
        else if (ownerHandle == ::GetDesktopWindow())
        {
            transferIcons = false;
        }

        BaseWindow owner(ownerHandle);

        if (create(Style, ExStyle, title, nullptr, nullptr, nullptr, ownerHandle))
        {
            if (transferIcons)
            {
                std::pair<uint32_t, int> sizes[] = {
                    { ICON_SMALL, GCLP_HICONSM },
                    { ICON_BIG, GCLP_HICON }
                };

                for (const auto &iconSize : sizes)
                {
                    HICON iconHandle = owner.getIcon(iconSize.first);

                    if (iconHandle == nullptr)
                    {
                        iconHandle = reinterpret_cast<HICON>(owner.getClassLongValue(iconSize.second));
                    }

                    if (iconHandle != nullptr)
                    {
                        setIcon(iconHandle, iconSize.first);
                    }
                }
            }

            NONCLIENTMETRICSW ncMetrics;
            Ag::zeroFill(ncMetrics);
            ncMetrics.cbSize = sizeof(ncMetrics);

            HFONT dialogFont = nullptr;

            if (getSystemParametersInfo(SPI_GETNONCLIENTMETRICS,
                                        sizeof(ncMetrics), &ncMetrics))
            {
                _textFont = ::CreateFontIndirectW(&ncMetrics.lfMessageFont);
                dialogFont = _textFont;
            }

            if (_textFont == nullptr)
            {
                dialogFont = reinterpret_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT));
            }

            // Determine the icon to use.
            LPCWSTR iconResource;

            switch (icon)
            {
            case Icon::Information: iconResource = IDI_INFORMATION; break;
            case Icon::Warning: iconResource = IDI_WARNING; break;
            case Icon::Error: iconResource = IDI_ERROR; break;
            case Icon::Shield: iconResource = IDI_SHIELD; break;
            default: iconResource = IDI_QUESTION; break;
            }

            _image = ::LoadIconW(nullptr, iconResource);

            DeviceContext dc;
            dc.createFromWindow(*this);

            // Select the message box font for measuring text.
            HGDIOBJ oldFont = dc.select(dialogFont);

            constexpr double Spacing = 4.0;
            constexpr double ImageSpacing = 7.0;

            const PointD padding(7.0, 7.0);
            PointD dpi(dc.getDpiX(), dc.getDpiY());
            PointD iconSize = PointD::fromPixels(getSystemMetrics(SM_CXICON),
                                                 getSystemMetrics(SM_CYICON),
                                                 dpi);
            PointD iconOrigin = padding;
            _imageOrigin = padding.toPixelsRound(dpi);

            std::vector<ButtonInfo> buttonDefs;

            auto addButton = [&buttonDefs, &buttons, &defaultButton](MsgBox::Button button,
                                                                     Ag::utf8_cptr_t buttonText)
                {
                    if (buttons & button)
                    {
                        buttonDefs.emplace_back(buttonText, button);

                        return button == defaultButton;
                    }

                    return false;
                };


            bool hasDefault = false;

            if ((buttons == 0) || (buttons & MsgBox::OK))
            {
                buttonDefs.emplace_back("OK", Ag::toScalar(MsgBox::OK));
                hasDefault = (buttons == 0) || (defaultButton == MsgBox::OK);
                buttonDefs.front().IsDefault = hasDefault;
            }

            hasDefault |= addButton(MsgBox::Cancel, "Cancel");
            hasDefault |= addButton(MsgBox::TryAgain, "TryAgain");
            hasDefault |= addButton(MsgBox::Abort, "Abort");
            hasDefault |= addButton(MsgBox::Retry, "Retry");
            hasDefault |= addButton(MsgBox::Ignore, "Ignore");
            hasDefault |= addButton(MsgBox::Yes, "Yes");
            hasDefault |= addButton(MsgBox::No, "No");

            if (hasDefault == false)
            {
                // Make the first button the default.
                buttonDefs.front().IsDefault = true;
            }

            MarginD buttonBorder(2.0);
            MarginD buttonPadding(4.0, 2.0);
            SizeD minButtonSize(75.0, 23.0);
            size_t buttonCount = buttonDefs.size();
            double buttonsWidth = 0.0;
            double buttonHeight = 0.0;

            for (size_t i = 0; i < buttonCount; ++i)
            {
                ButtonInfo &info = buttonDefs[i];

                LegacyRect textRect;
                dc.measureText(info.Text, textRect, DT_SINGLELINE | DT_NOCLIP);
                RectD realRect = RectD::fromPixels(textRect, dpi);
                SizeD buttonSize = realRect.expand(buttonPadding).expand(buttonBorder).getExtents().max(minButtonSize);

                double buttonOffset = buttonsWidth;

                if (i > 0)
                    buttonOffset += Spacing;

                info.Placement = RectD(PointD(buttonOffset, 0.0), buttonSize);
                buttonsWidth = buttonOffset + buttonSize.getWidth();
                buttonHeight = std::max(buttonHeight, buttonSize.getHeight());
            }

            // Make the buttons all have the same height.
            for (ButtonInfo &info : buttonDefs)
            {
                info.Placement.setHeight(buttonHeight);
            }

            constexpr double TextWidth = 96.0 * 3;
            double effectiveTextWidth = std::max(TextWidth,
                                                 buttonsWidth - iconSize.getX() - ImageSpacing);
            PointD textOrigin = iconOrigin;
            textOrigin.deltaX(iconSize.getX() + ImageSpacing);

            PointD textExtreme = textOrigin;
            textExtreme.deltaX(effectiveTextWidth);

            // Calculate the origin and horizontal size of the text rectangle.
            _textRect = textOrigin.toPixelRect(textExtreme, dpi);

            // Calculate the vertical extent of the text rectangle.
            dc.measureText(message, _textRect, DT_NOCLIP | DT_WORDBREAK);

            // Calculate the position of the buttons centred below the text and image.
            RectD realTextRect = RectD::fromPixels(_textRect, dpi);
            PointD buttonOrigin(padding.getX(), realTextRect.getExtremeY() + Spacing);

            double totalWidth = realTextRect.getExtremeX() - padding.getX();
            double buttonOffset = std::max(totalWidth - buttonsWidth, 0.0) + padding.getX();

            dc.select(oldFont);
            dc.dispose();

            // Create buttons.
            double rightEdgeButton = 0;

            for (ButtonInfo &info : buttonDefs)
            {
                info.Placement.translateX(buttonOffset);
                info.Placement.setOriginY(buttonOrigin.getY());
                rightEdgeButton = info.Placement.getExtremeX();

                LegacyRect buttonRect = info.Placement.toPixels(dpi);
                std::wstring buffer = info.Text.toWide();

                DWORD style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON;

                if (info.IsDefault)
                {
                    style |= BS_DEFPUSHBUTTON;
                }

                HWND buttonHandle = ::CreateWindowExW(0, L"Button",
                                                      buffer.c_str(), style,
                                                      buttonRect.left,
                                                      buttonRect.top,
                                                      buttonRect.getWidth(),
                                                      buttonRect.getHeight(),
                                                      getHandle(),
                                                      reinterpret_cast<HMENU>(static_cast<uintptr_t>(info.CommandID)),
                                                      nullptr, nullptr);

                if (buttonHandle != nullptr)
                {
                    // Set the font of the button control.
                    ::SendMessageW(buttonHandle, WM_SETFONT,
                                   reinterpret_cast<WPARAM>(dialogFont), 0);
                }
            }

            // Calculate the total size of the client area.
            SizeD totalSize(rightEdgeButton + padding.getX(),
                            buttonOrigin.getY() + buttonHeight + padding.getY());

            // Re-position the dialog centred within its parent.
            LegacySize clientSize = totalSize.toPixels(dpi);
            LegacySize dialogSize = calculateWindowSizeForClient(clientSize);

            LegacyRect ownerRect = owner.getClientRect();
            LegacyRect ownerScreenRect = owner.clientToScreen(ownerRect);
            LegacyRect dialogRect = ownerScreenRect.centre(dialogSize);

            setPosition(dialogRect, SWP_NOZORDER | SWP_NOACTIVATE);

            isOK = true;
        }

        return isOK;
    }

    // Accessors
    Button getResult() const { return _result; }

protected:
    // Overrides
    virtual void processMessage(Message &message) override
    {
        CustomWindow::processMessage(message);

        if (message.getMessageId() == WM_PAINT)
        {
            DeviceContext dc;
            dc.createPaint(*this);

            ::DrawIcon(dc.getHandle(), _imageOrigin.x, _imageOrigin.y, _image);

            HFONT dialogFont = _textFont;

            if (dialogFont == nullptr)
            {
                dialogFont = reinterpret_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT));
            }

            HGDIOBJ oldFont = dc.select(dialogFont);
            dc.setBackgroundMode(TRANSPARENT);

            dc.drawText(_messageText.c_str(), _textRect, DT_WORDBREAK,
                        _messageText.length());

            dc.select(oldFont);
        }
        else if (message.getMessageId() == WM_COMMAND)
        {
            CommandMessage command(message);

            if (command.getNotifyCode() == BN_CLICKED)
            {
                _result = Ag::fromScalar<Button>(command.getCtrlID());
                message.setHandled();
                destroy();
            }
        }
        else if (message.getMessageId() == WM_CLOSE)
        {
            _result = MsgBox::Cancel;
            message.setHandled();
            destroy();
        }
    }

    virtual ATOM getRegisteredClass() const override
    {
        static ATOM classAtom = 0;

        if (classAtom == 0)
        {
            WNDCLASSEXW info;
            Ag::zeroFill(info);
            info.cbSize = sizeof(info);
            info.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
            info.lpszClassName = L"CustomMessageBox";
            info.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);

            if (auto guiApp = dynamic_cast<GuiApp *>(App::get()))
            {
                info.hIcon = guiApp->getAppIcon();
                info.hIconSm = guiApp->getSmallAppIcon();
            }

            classAtom = registerClass(info);
        }

        return classAtom;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
bool isWindowValid(uintptr_t context)
{
    return ::IsWindow(reinterpret_cast<HWND>(context)) != FALSE;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// MessageBox Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Displays a modal message box while still running the local thread
//! message loop and any related idle tasks.
//! @param[in] owner The window which owns the message box.
//! @param[in] message The message text to display.
//! @param[in] title The text to appear in the title of the message box.
//! @param[in] buttons The buttons to show in the message box.
//! @param[in] icon The icon image to show next to the message.
//! @param[in] defaultButton The button to push if return or space is pressed.
//! @return The button the user pushed to close the message box or
//! MessageBox::Cancel if they hit the close icon.
Button show(const BaseWindow &owner,
            Ag::string_cref_t message, Ag::string_cref_t title,
            uint32_t buttons, Icon icon,
            Button defaultButton)
{
    return show(owner.getHandle(), message, title, buttons, icon, defaultButton);
}

//! @brief Displays a modal message box while still running the local thread
//! message loop and any related idle tasks.
//! @param[in] ownerHandle The handle of the window which owns the message box.
//! @param[in] message The message text to display.
//! @param[in] title The text to appear in the title of the message box.
//! @param[in] buttons The buttons to show in the message box.
//! @param[in] icon The icon image to show next to the message.
//! @param[in] defaultButton The button to push if return or space is pressed.
//! @return The button the user pushed to close the message box or
//! MessageBox::Cancel if they hit the close icon.
Button show(HWND ownerHandle,
            Ag::string_cref_t message, Ag::string_cref_t title,
            uint32_t buttons, Icon icon,
            Button defaultButton)
{
    MessageDialog dialog;

    if (dialog.createInstance(ownerHandle, message, title, buttons, icon, defaultButton))
    {
        Modaliser makeModal(ownerHandle, dialog.getHandle(), nullptr);

        dialog.show(SW_SHOW);

        // Run the message loop until the dialog is destroyed.
        Dispatcher dispatcher;

        dispatcher.execConditional(isWindowValid,
                                   reinterpret_cast<uintptr_t>(dialog.getHandle()));
    }

    return dialog.getResult();
}

}}} // namespace Ag::Win32::MsgBox
////////////////////////////////////////////////////////////////////////////////
