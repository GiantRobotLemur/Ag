//! @file Ag/Win32Base/DeviceContext.hpp
//! @brief The declaration of an object wrapping a GDI device context.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_DEVICE_CONTEXT_HPP__
#define __AG_WIN32_BASE_DEVICE_CONTEXT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Win32API.hpp"

#include "Ag/Core/String.hpp"
#include "Brush.hpp"
#include "Font.hpp"
#include "Pen.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class BaseWindow;

//! @brief An object wrapping a GDI device context.
class DeviceContext
{
public:
    // Public Types
    //! @brief Describes the type of device context, implying the method required
    //! for destruction.
    enum DeviceType
    {
        //! @brief The device is of unknown source and no disposal action will occur.
        DT_Attached,

        //! @brief It is a display device created using GetDC(), ReleaseDC() will
        //! be called on disposal.
        DT_Window,

        //! @brief It is a display device created by BeginPaint(), EndPaint()
        //! will be called at destruction.
        DT_Paint,

        //! @brief It is a device which records graphic commands as an Enhanced
        //! Windows Metafile and will be disposed of using ReleaseDC() if the
        //! device isn't first closed to crate an metafile.
        DT_EnhMetafile,

        //! @brief It is a device created using CreateDC() or CreateIC(), such
        //! as a printer or display, DeleteDC() will be used to dispose of the
        //! device.
        DT_Device,

        //! @brief The device renders to the image currently selected into the
        //! device.
        DT_Memory,
    };

    // Construction/Destruction
    DeviceContext();
    DeviceContext(HDC attachedDevice);
    DeviceContext(const DeviceContext &&) = delete;
    DeviceContext(DeviceContext &&rhs) = delete;
    virtual ~DeviceContext();

    // Accessors
    bool isBound() const;
    HDC getHandle() const;
    bool tryGetBounds(RECT &bounds) const;
    const PAINTSTRUCT &getPaintInfo() const;
    int getDpiX() const;
    int getDpiY() const;
    HGDIOBJ getSelectedObjectHandle(GdiResourceType resourceType) const;
    GdiResource getSelectedObject(GdiResourceType resourceType) const;
    COLORREF getTextColour() const;
    COLORREF setTextColour(COLORREF colour) const;
    COLORREF getBackgroundColour() const;
    COLORREF setBackgroundColour(COLORREF colour) const;
    int getBackgroundMode() const;
    int setBackgroundMode(int mode) const;

    // Operations
    int saveState() const;
    void restoreState(int stateId) const;
    HGDIOBJ select(HGDIOBJ gdiObj) const;
    HGDIOBJ selectStock(int stockObjectId) const;
    Brush selectBrush(const Brush &brush) const;
    Font selectFont(const Font &font) const;
    Pen selectPen(const Pen &pen) const;
    void getDefaultFontDefinition(LOGFONTW &fontInfo) const;

    void createFromWindow(HWND handle);
    void createFromWindow(const BaseWindow &window);
    void createPaint(HWND handle);
    void createPaint(const BaseWindow &window);
    void createDevice(const String &driver,
                      const String &device,
                      const DEVMODEW *deviceMode = nullptr);
    void createDeviceInfo(const String &driver,
                          const String &device,
                          const DEVMODEW *deviceMode = nullptr);
    void createMemory(HDC refDevice);
    void createMemory(const DeviceContext &refDevice);
    void createEnhMetafile(HDC refDevice, const String &filename,
                           const RECT *bounds, const String &appName,
                           const String &description);
    void createEnhMetafile(const DeviceContext refDevice, const String &filename,
                           const RECT *bounds, const String &appName,
                           const String &description);
    void createMemoryEnhMetafile(HDC refDevice, const RECT *bounds,
                                 const String &appName,
                                 const String &description);
    void createMemoryEnhMetafile(const DeviceContext refDevice,
                                 const RECT *bounds,
                                 const String &appName,
                                 const String &description);
    HENHMETAFILE closeEnhMetafile();

    bool moveTo(const POINT &pt) const;
    bool lineTo(const POINT &pt) const;
    bool polylineTo(const POINT *points, size_t count) const;
    bool cubicBezierTo(const POINT *points, size_t count) const;
    bool drawLine(int x1, int y1, int x2, int y2) const;
    bool drawFilledRect(const RECT &area, const Brush &fillStyle) const;
    bool drawSimpleText(const POINT &origin, string_cref_t text) const;
    bool drawText(Ag::string_cref_t text, const RECT &bounds, uint32_t format) const;
    bool drawText(wchar_cptr_t text, const RECT &bounds, uint32_t format, size_t textLength = 0) const;
    bool drawModifiedText(Ag::string_ref_t text, const RECT &bounds, uint32_t format) const;
    bool measureText(Ag::string_cref_t text, RECT &bounds, uint32_t format) const;
    bool drawIcon(HICON handle, const POINT &origin) const;
    bool drawPolyPolygon(const POINT *points, const int *indices, int indexCount) const;

    void detach();
    void dispose();
    DeviceContext &operator=(const DeviceContext &) = delete;
    DeviceContext &operator=(DeviceContext &&rhs) = delete;
private:
    // Internal Types

    // Internal Functions
    void updateBounds(HBITMAP handle) const;

    // Internal Fields
    HDC _handle;
    HWND _window;
    PAINTSTRUCT _paintInfo;
    DeviceType _type;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
