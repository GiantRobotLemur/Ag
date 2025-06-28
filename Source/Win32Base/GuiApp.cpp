//! @file Win32Base/GuiApp.cpp
//! @brief The definition of an object which represents an application with a
//! graphical user interface of one kind or another.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/GuiApp.hpp"
#include "Ag/Win32Base/Tools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs a new object representing the GUI application and its main thread.
GuiApp::GuiApp() :
    _appIcon(nullptr),
    _appIconSmall(nullptr),
    _destroyIconResources(false)
{
}

//! @brief Ensures any loaded custom icon resources are disposed of.
GuiApp::~GuiApp()
{
    disposeOfIconResources();
}

//! @brief Gets the application icon resource, if one was loaded.
HICON GuiApp::getAppIcon() const
{
    return _appIcon;
}

//! @brief Gets the small application icon resource, if one was loaded.
HICON GuiApp::getSmallAppIcon() const
{
    return _appIconSmall;
}

//! @brief Gets the dispatcher object created on the same thread the application
//! object was created on.
Dispatcher &GuiApp::getMainThreadDispatcher()
{
    return _mainThreadDispatcher;
}

//! @brief Loads a custom icon resource to represent the application.
//! @param[in] module The handle to the module containing the resource, nullptr
//! for a shared icon.
//! @param[in] resourceID The numeric identifier of the icon resource, such as
//! a custom resource identifier or IDI_APPLICATION.
void GuiApp::loadAppIconResource(HINSTANCE module, uint32_t resourceID)
{
    disposeOfIconResources();

    uint32_t dpi = ::GetSystemDpiForProcess(::GetCurrentProcess());

    _appIcon = static_cast<HICON>(::LoadImageW(module,
                                               makeResourceText(resourceID),
                                               IMAGE_ICON, 0, 0,
                                               LR_DEFAULTSIZE));

    _appIconSmall = static_cast<HICON>(::LoadImageW(module,
                                                    makeResourceText(resourceID),
                                                    IMAGE_ICON,
                                                    ::GetSystemMetricsForDpi(SM_CXSMICON, dpi),
                                                    ::GetSystemMetricsForDpi(SM_CYSMICON, dpi),
                                                    0));

    // Only destroy the icons if they weren't shared.
    _destroyIconResources = (module != nullptr);
}

//! @brief Loads a custom icon resource to represent the application.
//! @param[in] module The handle to the module containing the resource, nullptr
//! for a shared icon.
//! @param[in] resourceID The name of the icon resource, such as
//! a custom resource identifier or IDI_APPLICATION.
void GuiApp::loadAppIconResource(HINSTANCE module, LPCWSTR resourceID)
{
    disposeOfIconResources();

    uint32_t dpi = ::GetSystemDpiForProcess(::GetCurrentProcess());

    _appIcon = static_cast<HICON>(::LoadImageW(module,
                                               resourceID,
                                               IMAGE_ICON, 0, 0,
                                               LR_DEFAULTSIZE));

    _appIconSmall = static_cast<HICON>(::LoadImageW(module,
                                                    resourceID,
                                                    IMAGE_ICON,
                                                    ::GetSystemMetricsForDpi(SM_CXSMICON, dpi),
                                                    ::GetSystemMetricsForDpi(SM_CYSMICON, dpi),
                                                    0));

    // Only destroy the icons if they weren't shared.
    _destroyIconResources = (module != nullptr);
}

//! @brief Should be called by derived classes to enable GUI App-specific
//! initialisation.
bool GuiApp::initialise(const Cli::ProgramArguments * /* args */)
{
    ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    return true;
}

//! @brief Runs the main thread dispatcher until exit is requested or WM_QUIT is
//! processed.
int GuiApp::run()
{
    return _mainThreadDispatcher.exec();
}

//! @brief Ensures that any custom loaded icon resources are disposed of.
void GuiApp::disposeOfIconResources()
{
    if (_destroyIconResources)
    {

        if (_appIcon != nullptr)
        {
            ::DestroyIcon(_appIcon);
        }

        if (_appIconSmall != nullptr)
        {
            ::DestroyIcon(_appIconSmall);
        }
    }

    _appIcon = nullptr;
    _appIconSmall = nullptr;
    _destroyIconResources = false;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
