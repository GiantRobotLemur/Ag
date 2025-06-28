//! @file Ag/Win32Base/CustomWindow.hpp
//! @brief The declaration of an object which wraps a handle to a top-level
//! window and processes its messages.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2023
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_CUSTOM_WINDOW_HPP__
#define __AG_WIN32_BASE_CUSTOM_WINDOW_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Window.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class String;

namespace Win32 {
//! @brief An object which wraps a handle to a top-level window and processes
//! its messages.
class CustomWindow : public Window
{
public:
    // Construction/Destruction
    CustomWindow();
    virtual ~CustomWindow();

    // Accessors
    HFONT getDefaultFont() const;

    // Operations
    bool create(uint32_t style, uint32_t exStyle, const String &title,
                PPOINT position = nullptr, PSIZE size = nullptr,
                HMENU menuHandle = nullptr,
                HWND ownerHandle = nullptr);

protected:
    // Overrides
    virtual void processMessage(Message &message) override;
    virtual void onCreate(Message &message);
    virtual void onDpiScaleChange(uint32_t xDpi, uint32_t yDpi,
                                  const RECT &recommendedResize);

    //! @brief Lazily registers the window type so that instances can be created.
    //! @returns The atom representing the registered class.
    //! @details Implementations should have an ATOM static variable to keep
    //! track of the registration state and call BaseWindow::registerClass() in
    //! order to initialise it on first call.
    virtual ATOM getRegisteredClass() const = 0;
private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    mutable HFONT _defaultFont;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
