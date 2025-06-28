//! @file Ag/Win32Base/GuiApp.hpp
//! @brief The declaration of an object which represents an application with a
//! graphical user interface of one kind or another.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GUI_APP_HPP__
#define __AG_WIN32_BASE_GUI_APP_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/App.hpp"
#include "Dispatcher.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which represents an application with a graphical user
//! interface of one kind or another.
class GuiApp : public App
{
public:
    // Construction/Destruction
    GuiApp();
    virtual ~GuiApp();

    // Accessors
    HICON getAppIcon() const;
    HICON getSmallAppIcon() const;
    Dispatcher &getMainThreadDispatcher();

    // Operations
    void loadAppIconResource(HINSTANCE module, uint32_t resourceID);
    void loadAppIconResource(HINSTANCE module, LPCWSTR resourceID);
protected:
    // Overrides
    virtual bool initialise(const Cli::ProgramArguments *args) override;
    virtual int run() override;
private:
    // Internal Functions
    void disposeOfIconResources();

    // Internal Fields
    Dispatcher _mainThreadDispatcher;
    HICON _appIcon;
    HICON _appIconSmall;
    bool _destroyIconResources;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
