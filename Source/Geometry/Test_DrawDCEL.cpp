//! @file Geometry/Test_DrawDCEL.cpp
//! @brief The definition of a GUI application which displays geometry output
//! to test algorithms.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Test_DrawScene.hpp"
#include "Test_GlyphData.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing the application window.
class DrawWindow
{
private:
    // Internal Types

    // Internal Fields
    HWND _handle;
    std::unique_ptr<Scene> _scene;

    // Internal Functions
    void draw(HDC deviceContext, RECT &drawArea, RECT &updateArea)
    {
    }

    bool processMessage(uint32_t id, uintptr_t /*wParam*/, intptr_t lParam, intptr_t &result)
    {
        result = 0;
        bool isHandled = false;

        if (id == WM_CLOSE)
        {
            ::DestroyWindow(_handle);
            ::PostQuitMessage(0);
            isHandled = true;
        }
        else if ((id == WM_DPICHANGED) && (lParam != 0))
        {
            // Resize the window to the new size based on the DPI scale change.
            LPRECT newPos = reinterpret_cast<LPRECT>(lParam);

            ::SetWindowPos(_handle, nullptr, newPos->left, newPos->top,
                           newPos->right - newPos->left,
                           newPos->bottom - newPos->top,
                           SWP_NOZORDER | SWP_NOACTIVATE);
            isHandled = true;
        }
        else if (id == WM_PAINT)
        {
            PAINTSTRUCT ps;
            RECT drawArea;

            if (::GetClientRect(_handle, &drawArea))
            {
                HDC deviceContext = ::BeginPaint(_handle, &ps);
                draw(deviceContext, drawArea, ps.rcPaint);
                ::EndPaint(_handle, &ps);
                isHandled = true;
            }
        }

        return isHandled;
    }

    static LRESULT CALLBACK messageCallback(HWND handle, UINT id, WPARAM wParam, LPARAM lParam)
    {
        DrawWindow *window = reinterpret_cast<DrawWindow *>(::GetWindowLongPtrW(handle, GWLP_USERDATA));

        if ((window == nullptr) && (lParam != 0) &&
            ((id == WM_CREATE) || (id == WM_NCCREATE)))
        {
            LPCREATESTRUCTW info = reinterpret_cast<LPCREATESTRUCTW>(lParam);

            window = reinterpret_cast<DrawWindow *>(info->lpCreateParams);

            if (window != nullptr)
            {
                window->_handle = handle;
                ::SetWindowLongPtrW(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            }
        }

        intptr_t result = 0;
        if ((window == nullptr) ||
            (window->processMessage(id, wParam, lParam, result) == false))
        {
            result = ::DefWindowProcW(handle, id, wParam, lParam);
        }

        if ((id == WM_DESTROY) && (window != nullptr))
        {
            ::SetWindowLongPtrW(handle, GWLP_USERDATA, 0);
            window->_handle = nullptr;
        }

        return result;
    }
public:
    // Construction/Destruction
    DrawWindow() :
        _handle(nullptr),
        _scene(std::make_unique<Scene>())
    {
    }

    // Accessors
    Scene *getScene() { return _scene.get(); }

    // Operations
    bool create()
    {
        WNDCLASSEXW cls;
        Ag::zeroFill(cls);
        HINSTANCE moduleHandle = ::GetModuleHandleW(nullptr);

        cls.cbSize = sizeof(cls);
        cls.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
        cls.hIcon = ::LoadIconW(nullptr, IDI_WINLOGO);
        cls.hIconSm = ::LoadIconW(nullptr, IDI_WINLOGO);
        cls.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        cls.hInstance = moduleHandle;
        cls.lpszClassName = L"DrawGeometryWindow";
        cls.lpfnWndProc = messageCallback;
        
        ATOM classID = ::RegisterClassExW(&cls);

        if (classID == 0)
            return false;

        constexpr DWORD Style = WS_OVERLAPPEDWINDOW;
        constexpr DWORD StyleEx = WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW;

        HWND handle = ::CreateWindowExW(StyleEx, reinterpret_cast<LPCWSTR>(classID),
                                        L"Draw Geometry Test", Style,
                                        CW_USEDEFAULT, CW_USEDEFAULT,
                                        CW_USEDEFAULT, CW_USEDEFAULT,
                                        ::GetDesktopWindow(), nullptr,
                                        moduleHandle, this);

        if (handle == nullptr)
        {
            return false;
        }
        else
        {
            _handle = handle;
            _scene->loadGeometry(Pound_Vertices, std::size(Pound_Vertices),
                                 Pound_Indices, std::size(Pound_Indices));
            return true;
        }
    }

    void show()
    {
        if (_handle != nullptr)
        {
            ::ShowWindow(_handle, SW_SHOW);
            ::UpdateWindow(_handle);
        }
    }
};

//! @brief An object representing the application.
class DrawApp : public Ag::App
{
private:
    // Internal Types

    // Internal Fields
    DrawWindow _window;

    // Internal Functions
public:
    // Construction/Destruction
    DrawApp() = default;
    virtual ~DrawApp() = default;

    // Accessors

    // Operations

protected:
    // Overrides
    virtual bool initialise(const Ag::Cli::ProgramArguments */*args*/) override
    {
        ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

        return _window.create();
    }

    virtual int run()
    {
        _window.show();

        MSG current;

        while (::GetMessageW(&current, nullptr, 0, 0))
        {
            ::TranslateMessage(&current);
            ::DispatchMessageW(&current);
        }

        return static_cast<int>(current.wParam);
    }
    //virtual void shutdown();
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Xxx Member Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_MAIN(DrawApp);

////////////////////////////////////////////////////////////////////////////////

