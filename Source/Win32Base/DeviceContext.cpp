//! @file Win32Base/DeviceContext.cpp
//! @brief The definition of an object wrapping a GDI device context.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
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
#include <iterator>
#include <string>
#include <utility>

#include <Windows.h>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Win32Base/BaseWindow.hpp"
#include "Ag/Win32Base/DeviceContext.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Win32 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Create the description string read for a call to CreateEnhMetaFile().
//! @param[out] buffer The buffer to hold wide character data.
//! @param[in] appName The name of the application which is creating the metafile.
//! @param[in] description The description of the image.
//! @return A pointer to the wide description field, possibly within buffer.
LPCWSTR createMetafileDescription(std::wstring &buffer, const String &appName,
                                  const String &description)
{
    LPCWSTR desc = nullptr;

    if ((appName.isEmpty() == false) || (description.isEmpty() == false))
    {
        buffer = appName.toWide();

        if (description.isEmpty())
        {
            buffer.append(3, L'\0');
        }
        else
        {
            Utf::appendToWide(buffer, description.getUtf8Bytes(),
                              description.getUtf8Length(),
                              description.getWideLength());
            buffer.append(2, L'\0');
        }

        desc = buffer.c_str();
    }

    return desc;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object not bound to any device context.
DeviceContext::DeviceContext() :
    _handle(nullptr),
    _window(nullptr),
    _type(DT_Attached)
{
    zeroFill(_paintInfo);
}

//! @brief Constructs an object attached to a device which makes no attempt to
//! manage its lifetime.
//! @param[in] attachedDevice The handle to the device to attach to.
//! @note As the object has no idea as to the origin of the device, calls to
//! tryGetBounds() will always fail.
DeviceContext::DeviceContext(HDC attachedDevice) :
    _handle(attachedDevice),
    _window(nullptr),
    _type(DT_Attached)
{
    zeroFill(_paintInfo);
}

//! @brief Ensure that any outstanding bound device context is appropriately
//! disposed of.
DeviceContext::~DeviceContext()
{
    dispose();
}

//! @brief Determines if the object is bound to an actual device context resource.
bool DeviceContext::isBound() const
{
    return _handle != nullptr;
}

//! @brief Gets the GDI handle to the device context.
HDC DeviceContext::getHandle() const
{
    return _handle;
}

//! @brief Attempts to get the bounds of the area which can be rendered into.
//! @param[out] bounds Receives the bounds of the area which can be rendered to
//! in device units.
//! @retval true The device had bounds which were returned.
//! @retval false The device was an enhanced metafile where no bounds were stated
//! at creation or a memory device with no target bitmap selected.
bool DeviceContext::tryGetBounds(RECT &bounds) const
{
    bounds = _paintInfo.rcPaint;

    return (bounds.right != bounds.left) && (bounds.top != bounds.bottom);
}

//! @brief Gets the WM_PAINT information associated with the device.
//! @return A reference to the internal data. If the object was not bound or
//! initialised using createPaint() some or all fields will be zeroed.
const PAINTSTRUCT &DeviceContext::getPaintInfo() const
{
    return _paintInfo;
}

//! @brief Gets the count of device units per horizontal inch.
int DeviceContext::getDpiX() const
{
    int dpi = 96;

    if (isBound())
    {
        dpi = ::GetDeviceCaps(_handle, LOGPIXELSX);
    }

    return dpi;
}

//! @brief Gets the count of device units per vertical inch.
int DeviceContext::getDpiY() const
{
    int dpi = 96;

    if (isBound())
    {
        dpi = ::GetDeviceCaps(_handle, LOGPIXELSY);
    }

    return dpi;
}

//! @brief Gets the handle of the currently selected resource of a specific type.
//! @param[in] resourceType The type of resource to return.
//! @return The handle of the object of the specified type selected for use
//! in the device context.
HGDIOBJ DeviceContext::getSelectedObjectHandle(GdiResourceType resourceType) const
{
    HGDIOBJ objHandle = nullptr;

    if (isBound())
    {
        objHandle = ::GetCurrentObject(_handle, Ag::toScalar(resourceType));
    }

    return objHandle;
}

//! @brief Gets the handle of the currently selected resource of a specific type.
//! @param[in] resourceType The type of resource to return.
//! @return The an object wrapping the resource of the specified type selected
//! for use in the device context.
GdiResource DeviceContext::getSelectedObject(GdiResourceType resourceType) const
{
    return isBound() ? GdiResource(::GetCurrentObject(_handle,
                                                      Ag::toScalar(resourceType))) :
                       GdiResource();
}

//! @brief Gets the text colour.
COLORREF DeviceContext::getTextColour() const
{
    return ::GetTextColor(_handle);
}

//! @brief Sets the text colour.
//! @param[in] colour The new text colour.
//! @return The previously set text colour.
COLORREF DeviceContext::setTextColour(COLORREF colour) const
{
    return ::SetTextColor(_handle, colour);
}

//! @brief Gets the current background colour.
COLORREF DeviceContext::getBackgroundColour() const
{
    return ::GetBkColor(_handle);
}

//! @brief Sets the current background colour to the specified colour value,
//! or to the nearest physical colour if the device cannot represent the
//! specified colour value.
//! @param[in] colour The new background colour.
//! @return The old background colour or CLR_INVALID if the function fails.
COLORREF DeviceContext::setBackgroundColour(COLORREF colour) const
{
    return ::SetBkColor(_handle, colour);
}

//! @brief Gets the current background mix mode.
int DeviceContext::getBackgroundMode() const
{
    return ::GetBkMode(_handle);
}

//! @brief Sets the background mix mode.
//! @param[in] mode The new mode, either OPAQUE or TRANSPARENT.
//! @return The old mode.
int DeviceContext::setBackgroundMode(int mode) const
{
    return ::SetBkMode(_handle, mode);
}

//! @brief Saves the state of the device on an internal stack.
//! @return An identifier of the state saved to be passed to restoreState() later.
int DeviceContext::saveState() const
{
    int stateId = 0;

    if (isBound())
    {
        stateId = ::SaveDC(_handle);
    }

    return stateId;
}

//! @brief Restores the state of the device.
//! @param stateId A state identifier previously returned by saveState().
void DeviceContext::restoreState(int stateId) const
{
    if (isBound())
    {
        ::RestoreDC(_handle, stateId);
    }
}

//! @brief Selects an un-typed object for use with the device.
//! @param[in] gdiObj The handle to the brush, pen, bitmap, region, etc. to
//! select.
//! @return The handle to the previously selected object of the same type.
HGDIOBJ DeviceContext::select(HGDIOBJ gdiObj) const
{
    HGDIOBJ oldHandle = nullptr;

    if (_handle == nullptr)
    {
        throw ObjectNotBoundException("GDI device context", "SelectObject()");
    }
    else if (gdiObj == nullptr)
    {
        throw ArgumentException("gdiObj");
    }
    else
    {
        if ((_type == DT_Memory) && (::GetObjectType(gdiObj) == OBJ_BITMAP))
        {
            // If we are selecting a bitmap, get its size to serve as the
            // current object bounds.
            updateBounds(static_cast<HBITMAP>(gdiObj));
        }

        oldHandle = ::SelectObject(_handle, gdiObj);
    }

    return oldHandle;
}

//! @brief Selects an un-typed stock object for use with the device.
//! @param[in] stockObjectId The identifier of a stock brush, pen, font, etc.
//! such as DEFAULT_GUI_FONT, BLACK_BRUSH, WHITE_PEN.
//! @return The handle to the previously selected object of the same type.
HGDIOBJ DeviceContext::selectStock(int stockObjectId) const
{
    return select(::GetStockObject(stockObjectId));
}

//! @brief Selects a brush for use in the current device context.
//! @param[in] brush An object wrapping the brush resource to select.
//! @return An object representing the previously selected brush.
Brush DeviceContext::selectBrush(const Brush &brush) const
{
    HGDIOBJ oldBrush = select(brush.getHandle());

    return Brush(static_cast<HBRUSH>(oldBrush), false);
}

//! @brief Selects a font for use in the current device context.
//! @param[in] font An object wrapping the font resource to select.
//! @return An object representing the previously selected font.
Font DeviceContext::selectFont(const Font &font) const
{
    HGDIOBJ oldFont = select(font.getHandle());

    return Font(static_cast<HFONT>(oldFont), false);
}

//! @brief Selects a pen for use in the current device context.
//! @param[in] pen An object wrapping the pen resource to select.
//! @return An object representing the previously selected pen.
Pen DeviceContext::selectPen(const Pen &pen) const
{
    HGDIOBJ oldPen = select(pen.getHandle());

    return Pen(static_cast<HPEN>(oldPen), false);
}

//! @brief Gets the font configured for use in system message boxes
//! as an approximation of a default GUI font.
//! @param[out] fontInfo The structure to receive the font definition.
void DeviceContext::getDefaultFontDefinition(LOGFONTW &fontInfo) const
{
    zeroFill(fontInfo);

    NONCLIENTMETRICSW ncMetrics;
    zeroFill(ncMetrics);
    ncMetrics.cbSize = sizeof(ncMetrics);

    if (::SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof(ncMetrics),
                                &ncMetrics, 0))
    {
        fontInfo = ncMetrics.lfMessageFont;
    }
    else
    {
        // Use the stock font, which is not a good representation of
        // a default font, but it will do.
        HGDIOBJ defaultGuiFontHandle = ::GetStockObject(DEFAULT_GUI_FONT);

        ::GetObjectW(defaultGuiFontHandle, sizeof(fontInfo), &fontInfo);
    }

    int dpi = ::GetDeviceCaps(_handle, LOGPIXELSX);

    if (dpi != 96)
    {
        // Adjust the size of the font for non-default DPI.
        fontInfo.lfHeight = (fontInfo.lfHeight * dpi) / 96;
    }
}

//! @brief Creates a device context to the client area of a window.
//! @param[in] handle The handle of the window to render to.
void DeviceContext::createFromWindow(HWND handle)
{
    dispose();

    if (::IsWindow(handle) == FALSE)
    {
        throw ArgumentException("handle");
    }

    _handle = ::GetDC(handle);

    if (_handle == nullptr)
    {
        throw Win32Exception("GetDC()", ::GetLastError());
    }
    else
    {
        _type = DT_Window;
        _window = handle;
        ::GetClientRect(_window, &_paintInfo.rcPaint);
    }
}

//! @brief Creates a device context to the client area of a window.
//! @param[in] window The object representing the window to render to.
void DeviceContext::createFromWindow(const BaseWindow &window)
{
    dispose();

    if (window.isBound())
    {
        createFromWindow(window.getHandle());
    }
    else
    {
        throw ArgumentException("window");
    }
}

//! @brief Bounds the object to a device context used to service the
//! WM_PAINT message.
//! @param[in] handle The handle to the window to be repainted.
void DeviceContext::createPaint(HWND handle)
{
    dispose();

    if (::IsWindow(handle) == FALSE)
    {
        throw ArgumentException("handle");
    }

    _handle = ::BeginPaint(handle, &_paintInfo);

    if (_handle == nullptr)
    {
        throw Win32Exception("BeginPaint()", ::GetLastError());
    }
    else
    {
        _type = DT_Paint;
        _window = handle;
    }
}

//! @brief Bounds the object to a device context used to service the
//! WM_PAINT message.
//! @param[in] window The object representing the window to be repainted.
void DeviceContext::createPaint(const BaseWindow &window)
{
    dispose();

    if (window.isBound())
    {
        createPaint(window.getHandle());
    }
    else
    {
        throw ArgumentException("window");
    }
}

//! @brief Bind the object to a device context created to draw to a specific
//! device.
//! @param[in] driver The name of the driver, perhaps "DISPLAY" for the entire
//! display or empty for a printer.
//! @param[in] device The specific output device to draw to, possibly empty
//! for a display device.
//! @param[in] deviceMode Optional device-specific initialisation parameters.
void DeviceContext::createDevice(const String &driver,
                                 const String &device,
                                 const DEVMODEW *deviceMode /* = nullptr */)
{
    dispose();

    std::wstring wideDriver = driver.toWide(),
                 wideDevice = device.toWide();

    _handle = ::CreateDCW(wideDriver.empty() ? nullptr : wideDriver.c_str(),
                          wideDevice.empty() ? nullptr : wideDevice.c_str(),
                          nullptr, deviceMode);

    if (_handle == nullptr)
    {
        throw Win32Exception("CreateDC()", ::GetLastError());
    }
    else
    {
        _type = DT_Device;
        _paintInfo.rcPaint.right = ::GetDeviceCaps(_handle, HORZRES);
        _paintInfo.rcPaint.bottom = ::GetDeviceCaps(_handle, VERTRES);
    }
}

//! @brief Bind the object to an information-only device context created to
//! interrogate the properties of a specific device.
//! @param[in] driver The name of the driver, perhaps "DISPLAY" for the entire
//! display or empty for a printer.
//! @param[in] device The specific output device to draw to, possibly empty
//! for a display device.
//! @param[in] deviceMode Optional device-specific initialisation parameters.
void DeviceContext::createDeviceInfo(const String &driver,
                                     const String &device,
                                     const DEVMODEW *deviceMode)
{
    dispose();

    std::wstring wideDriver = driver.toWide(),
        wideDevice = device.toWide();

    _handle = ::CreateICW(wideDriver.empty() ? nullptr : wideDriver.c_str(),
                          wideDevice.empty() ? nullptr : wideDevice.c_str(),
                          nullptr, deviceMode);

    if (_handle == nullptr)
    {
        throw Win32Exception("CreateIC()", ::GetLastError());
    }
    else
    {
        _type = DT_Device;
        _paintInfo.rcPaint.right = ::GetDeviceCaps(_handle, HORZRES);
        _paintInfo.rcPaint.bottom = ::GetDeviceCaps(_handle, VERTRES);
    }
}

//! @brief Creates a memory device context compatible with a reference device.
//! @param[in] refDevice The handle of the reference device to copy attributes from.
void DeviceContext::createMemory(HDC refDevice)
{
    dispose();

    if (refDevice == nullptr)
    {
        throw ArgumentException("refDevice");
    }

    _handle = ::CreateCompatibleDC(refDevice);

    if (_handle == nullptr)
    {
        throw Win32Exception("CreateCompatibleDC()", ::GetLastError());
    }
    else
    {
        _type = DT_Memory;

        // Calculate the bounds from the currently selected image.
        updateBounds(static_cast<HBITMAP>(::GetCurrentObject(_handle, OBJ_BITMAP)));
    }
}

//! @brief Creates a memory device context compatible with a reference device.
//! @param[in] refDevice The object wrapping the reference device to copy
//! attributes from.
void DeviceContext::createMemory(const DeviceContext &refDevice)
{
    createMemory(refDevice.getHandle());
}

//! @brief Creates a device which saves drawing instructions to a file as an
//! enhanced Windows Metafile.
//! @param[in] refDevice The handle to the reference device to copy
//! attributes from.
//! @param[in] filename The name of the file to write when the device is
//! disposed of.
//! @param[in] bounds The optional bounds of the image being created, nullptr
//! to calculate the bounds from the graphic operations recorded.
//! @param[in] appName The name of the application recording the graphics.
//! @param[in] description The description of the image being recorded.
void DeviceContext::createEnhMetafile(HDC refDevice, const String &filename,
                                      const RECT *bounds, const String &appName,
                                      const String &description)
{
    dispose();

    if (filename.isEmpty())
    {
        createMemoryEnhMetafile(refDevice, bounds, appName, description);
    }

    std::wstring wideFile = filename.toWide(), wideDesc;
    LPCWSTR desc = createMetafileDescription(wideDesc, appName, description);

    _handle = ::CreateEnhMetaFile(refDevice, wideFile.c_str(), bounds, desc);

    if (_handle == nullptr)
    {
        throw Win32Exception("CreateEnhMetaFile(File)", ::GetLastError());
    }
    else
    {
        _type = DT_EnhMetafile;

        if (bounds != nullptr)
        {
            // Copy the expected bounds.
            _paintInfo.rcPaint = *bounds;
        }
    }
}

//! @brief Creates a device which saves drawing instructions to a file as an
//! enhanced Windows Metafile.
//! @param[in] refDevice The object wrapping the reference device to copy
//! attributes from.
//! @param[in] filename The name of the file to write when the device is
//! disposed of.
//! @param[in] bounds The optional bounds of the image being created, nullptr
//! to calculate the bounds from the graphic operations recorded.
//! @param[in] appName The name of the application recording the graphics.
//! @param[in] description The description of the image being recorded.
void DeviceContext::createEnhMetafile(const DeviceContext refDevice,
                                      const String &filename,
                                      const RECT *bounds, const String &appName,
                                      const String &description)
{
    if (filename.isEmpty())
    {
        createMemoryEnhMetafile(refDevice.getHandle(), bounds,
                                appName, description);
    }
    else
    {
        createEnhMetafile(refDevice.getHandle(), filename, bounds,
                          appName, description);
    }
}

//! @brief Creates a device which saves drawing instructions as an object
//! in memory.
//! @param[in] refDevice The handle to the reference device to copy
//! attributes from.
//! @param[in] bounds The optional bounds of the image being created, nullptr
//! to calculate the bounds from the graphic operations recorded.
//! @param[in] appName The name of the application recording the graphics.
//! @param[in] description The description of the image being recorded.
//! @details A call to closeEnhMetafile() is required to harvest the recorded
//! graphic operations as an in-memory object.
void DeviceContext::createMemoryEnhMetafile(HDC refDevice, const RECT *bounds,
                                            const String &appName,
                                            const String &description)
{
    dispose();

    std::wstring buffer;
    LPCWSTR desc = createMetafileDescription(buffer, appName, description);

    _handle = ::CreateEnhMetaFileW(refDevice, nullptr, bounds, desc);

    if (_handle == nullptr)
    {
        throw Win32Exception("CreateEnhMetaFile(Memory)", ::GetLastError());
    }
    else
    {
        _type = DT_EnhMetafile;

        if (bounds != nullptr)
        {
            _paintInfo.rcPaint = *bounds;
        }
    }
}

//! @brief Creates a device which saves drawing instructions as an object
//! in memory.
//! @param[in] refDevice The object wrapping the reference device to copy
//! attributes from.
//! @param[in] bounds The optional bounds of the image being created, nullptr
//! to calculate the bounds from the graphic operations recorded.
//! @param[in] appName The name of the application recording the graphics.
//! @param[in] description The description of the image being recorded.
//! @details A call to closeEnhMetafile() is required to harvest the recorded
//! graphic operations as an in-memory object.
void DeviceContext::createMemoryEnhMetafile(const DeviceContext refDevice,
                                            const RECT *bounds,
                                            const String &appName,
                                            const String &description)
{
    createMemoryEnhMetafile(refDevice.getHandle(), bounds, appName, description);
}

//! @brief Disposes of the metafile device in order to create an in-memory
//! object representing the recorded graphic operations.
//! @return A handle to the recorded metafile.
//! @throws OperationException If the object was unbound or the device was not
//! created to record a metafile.
HENHMETAFILE DeviceContext::closeEnhMetafile()
{
    HENHMETAFILE metafileHandle = nullptr;

    if ((_type == DT_EnhMetafile) && (_handle != nullptr))
    {
        metafileHandle = ::CloseEnhMetaFile(_handle);
        _handle = nullptr;
        _type = DT_Attached;
        zeroFill(_paintInfo);

        if (metafileHandle == nullptr)
        {
            throw Win32Exception("CloseEnhMetaFile()", ::GetLastError());
        }
    }
    else
    {
        throw OperationException("Creating an in-memory enhanced metafile from "
                                 "a device of the wrong type.");
    }

    return metafileHandle;
}

//! @brief Moves the drawing cursor to a new position.
//! @param[in] pt The new position of the cursor in logical units.
//! @return A boolean value indicating if the operation was successful.
bool DeviceContext::moveTo(const POINT &pt) const
{
    return ::MoveToEx(_handle, pt.x, pt.y, nullptr) != FALSE;
}

//! @brief Draws a line using the current pen from the current cursor location
//! to a new location which the cursor location is set to.
//! @param[in] pt The end point of the line, in logical units.
//! @return A boolean value indicating if the operation was successful.
bool DeviceContext::lineTo(const POINT &pt) const
{
    return ::LineTo(_handle, pt.x, pt.y) != FALSE;
}

//! @brief Draws a number of line segments starting at the current cursor
//! position and updates it upon completion.
//! @param[in] points The ends points of the lines to draw.
//! @param[in] count The count of end points in @p points.
//! @return A boolean value indicating if the operation was successful.
bool DeviceContext::polylineTo(const POINT *points, size_t count) const
{
    return ::PolylineTo(_handle, points, static_cast<DWORD>(count)) != FALSE;
}

//! @brief Draws a number of cubic bezier starting at the current cursor
//! position and updates it upon completion.
//! @param[in] points An array of successive sets if two control points and an
//! end point which define successive curves.
//! @param[in] count The count of end points in @p points, this must be
//! divisible by 3.
//! @return A boolean value indicating if the operation was successful.
bool DeviceContext::cubicBezierTo(const POINT *points, size_t count) const
{
    return ::PolyBezierTo(_handle, points, static_cast<DWORD>(count)) != FALSE;
}

//! @brief Draw a line in the device using the currently selected pen and
//! updates the current drawing cursor position.
//! @param[in] x1 The horizontal offset of the start point, in logical units.
//! @param[in] y1 The vertical offset of the start point, in logical units.
//! @param[in] x2 The horizontal offset of the end point, in logical units.
//! @param[in] y2 The vertical offset of the end point, in logical units.
//! @return A boolean value indicating if the operation was successful.
bool DeviceContext::drawLine(int x1, int y1, int x2, int y2) const
{
    bool isOK = false;

    if (isBound())
    {
        isOK = (::MoveToEx(getHandle(), x1, y1, nullptr) != FALSE) &&
               (::LineTo(getHandle(), x2, y2) != FALSE);
    }

    return isOK;
}

//! @brief Fills a rectangle by using the specified brush.
//! @param[in] area The area to be filled.
//! @param[in] fillStyle The brush used to fill the area.
//! @return A boolean value indicating if the operation was successful.
bool DeviceContext::drawFilledRect(const RECT &area, const Brush &fillStyle) const
{
    bool isOK = false;

    if (isBound() && fillStyle.isBound())
    {
        isOK = ::FillRect(_handle, &area,
                          reinterpret_cast<HBRUSH>(fillStyle.getHandle())) != FALSE;
    }

    return isOK;
}

//! @brief Draws a simple single line of text.
//! @param[in] origin The origin point from which the text is drawn.
//! @param[in] text The text to draw.
//! @return A boolean value indicating whether the operation was successful.
bool DeviceContext::drawSimpleText(const POINT &origin, string_cref_t text) const
{
    bool isOK = false;

    if (isBound())
    {
        std::wstring buffer = text.toWide();

        isOK = ::TextOutW(getHandle(), origin.x, origin.y,
                          buffer.c_str(),
                          static_cast<int>(buffer.length())) != FALSE;
    }

    return isOK;
}

//! @brief Draws text using the DrawTextW() GDI function.
//! @param[in] text The text to draw.
//! @param[in] bounds The bounds in which the text is to be drawn.
//! @param[in] format The flags used to format the text, e.g. DT_EXPANDTABS.
//! @return A boolean value indicating whether the operation was successful.
//! @note The DT_MODIFYSTRING and DT_CALCRECT flags will be automatically
//! removed from the format flags.
bool DeviceContext::drawText(Ag::string_cref_t text, const RECT &bounds, uint32_t format) const
{
    bool isOK = false;

    if (text.isEmpty())
    {
        isOK = true;
    }
    else if (isBound())
    {
        std::vector<wchar_t> buffer;
        buffer.reserve(text.getWideLength() + 1);
        text.appendToWideBuffer(buffer);
        buffer.push_back(L'\0');

        isOK = drawText(buffer.data(), bounds, format, text.getWideLength());
    }

    return isOK;
}

//! @brief Draws text using the DrawTextW() GDI function.
//! @param[in] text The null-terminated or bounded array of wide characters
//! to draw.
//! @param[in] bounds The bounds in which the text is to be drawn.
//! @param[in] format The flags used to format the text, e.g. DT_EXPANDTABS.
//! @param[in] textLength The count of characters in text to draw or 0 if the
//! array is null-terminated.
//! @return A boolean value indicating whether the operation was successful.
//! @note The DT_MODIFYSTRING and DT_CALCRECT flags will be automatically
//! removed from the format flags.
bool DeviceContext::drawText(wchar_cptr_t text, const RECT &bounds,
                             uint32_t format, size_t textLength /*= 0*/) const
{
    bool isOK = false;

    if ((text == nullptr) || (*text == L'\0'))
    {
        isOK = true;
    }
    else
    {
        int effectiveLength = static_cast<int>(textLength);

        if (textLength == 0)
        {
            // Have DrawText() calculate the length.
            effectiveLength = -1;
        }

        uint32_t safeFormat = format & ~(DT_MODIFYSTRING | DT_CALCRECT);
        RECT writableBounds = bounds;

        isOK = ::DrawTextW(_handle, text, effectiveLength,
                           &writableBounds, safeFormat) != FALSE;
    }

    return isOK;
}

//! @brief Draws text using the DrawTextW() GDI function and updates the text
//! to reflect the actual characters rendered.
//! @param[in,out] text The text to draw, updated based on the use of formatting
//! flags DT_END_ELLIPSIS or DT_PATH_ELLIPSIS.
//! @param[in] bounds The bounds in which the text is to be drawn.
//! @param[in] format The flags used to format the text, e.g. DT_EXPANDTABS.
//! @return A boolean value indicating whether the operation was successful.
//! @note The DT_MODIFYSTRING flag will be automatically applied and the
//! DT_CALCRECT flag will be automatically removed from the format flags.
bool DeviceContext::drawModifiedText(Ag::string_ref_t text,
                                     const RECT &bounds,
                                     uint32_t format) const
{
    bool isOK = false;

    if (text.isEmpty())
    {
        isOK = true;
    }
    else if (isBound())
    {
        uint32_t safeFormat = (format | DT_MODIFYSTRING) & ~DT_CALCRECT;
        RECT writableBounds = bounds;

        constexpr size_t ExtraChars = 5;
        std::vector<wchar_t> buffer;
        buffer.reserve(text.getWideLength() + ExtraChars);
        text.appendToWideBuffer(buffer);
        std::fill_n(std::back_inserter(buffer), ExtraChars, L'\0');

        isOK = ::DrawTextW(_handle, buffer.data(), static_cast<int>(text.getWideLength()),
                           &writableBounds, safeFormat) != FALSE;

        if (isOK)
        {
            // Update the string with the contents of the modified buffer.
            text = Ag::String(buffer.data());
        }
    }

    return isOK;
}

//! @brief Measures a text using the DrawTextW() GDI function.
//! @param[in] text The text to measure.
//! @param[in,out] bounds On entry, specifies the origin and possibly the
//! width of the proposed output rectangle and has its width and height
//! updated based on the measured size of the text.
//! @param[in] format The flags used to format the text, e.g. DT_EXPANDTABS.
//! @return A boolean value indicating whether the operation was successful.
//! @note The DT_CALCRECT flag will be automatically applied and the
//! DT_MODIFYSTRING flag will be automatically removed from the format flags.
bool DeviceContext::measureText(Ag::string_cref_t text,
                                RECT &bounds, uint32_t format) const
{
    bool isOK = false;

    if (text.isEmpty())
    {
        isOK = true;
    }
    else if (isBound())
    {
        uint32_t safeFormat = (format | DT_CALCRECT) & ~DT_MODIFYSTRING;

        std::vector<wchar_t> buffer;
        buffer.reserve(text.getWideLength() + 1);
        text.appendToWideBuffer(buffer);
        buffer.push_back(L'\0');

        isOK = ::DrawTextW(_handle, buffer.data(),
                           static_cast<int>(text.getWideLength()),
                           &bounds, safeFormat) != FALSE;
    }

    return isOK;
}

//! @brief Draws an icon at the specified position.
//! @param[in] handle The handle of the icon resource to draw.
//! @param[in] origin The position of the origin of the icon.
//! @return A boolean value indicating whether the operation was successful.
bool DeviceContext::drawIcon(HICON handle, const POINT &origin) const
{
    bool isOK = false;

    if (isBound())
    {
        isOK = ::DrawIcon(_handle, origin.x, origin.y, handle) != FALSE;
    }

    return isOK;
}

//! @brief Draws a set of closed polygons outline with the current pen and
//! filled with the current brush.
//! @param[in] points The array of points representing all vertices.
//! @param[in] indices An array of counts of vertices representing each polygon
//! to draw.
//! @param[in] indexCount The count of elements in @p indices.
//! @return A boolean value indicating whether the operation was successful.
//! @throws ObjectDisposedException If the object was not bound to a device.
//! @throws ArgumentNullException If either @p points or @p indices are
//! nullptr.
bool DeviceContext::drawPolyPolygon(const POINT *points, const int *indices,
                                    int indexCount) const
{
    bool isOK = false;

    if (isBound() && (indexCount > 0))
    {
        if (points == nullptr)
            throw ArgumentNullException("points");

        if (indices == nullptr)
            throw ArgumentNullException("indices");

        isOK = ::PolyPolygon(_handle, points, indices, indexCount);
    }

    return isOK;
}

//! @brief Resets the object to an unbound state without disposing of any bound
//! resource.
//! @note This is only valid if the application takes responsibility for disposing
//! of the resource or because it was a DC owned by a window.
void DeviceContext::detach()
{
    _handle = nullptr;
    _window = nullptr;
    zeroFill(_paintInfo);
    _type = DT_Attached;
}

//! @brief Disposes of the device context in a manner appropriate to its type.
void DeviceContext::dispose()
{
    // Perform custom disposal.
    if (_handle != nullptr)
    {
        switch (_type)
        {
        case DT_Window:
            ::ReleaseDC(_window, _handle);
            break;

        case DT_Paint:
            ::EndPaint(_window, &_paintInfo);
            break;

        case DT_EnhMetafile:
            ::ReleaseDC(_window, _handle);
            break;

        case DT_Device:
        case DT_Memory:
            ::DeleteDC(_handle);
            break;
        }

        _handle = nullptr;
        _window = nullptr;
        zeroFill(_paintInfo);
        _type = DT_Attached;
    }
}

//! @brief Updates the bounds of the device according to the dimensions of the
//! currently selected image.
//! @param[in] handle The handle of the currently selected bitmap image.
void DeviceContext::updateBounds(HBITMAP handle) const
{
    // SORRY: const_cast<>() here because normally the bounds are const unless
    // we are wrapping a memory DC, then they change whenever a new bitmap
    // is selected. However, select() should not be a non-const member function.
    RECT *bounds = const_cast<PRECT>(&_paintInfo.rcPaint);

    bounds->left = 0;
    bounds->top = 0;

    BITMAP info;
    if (::GetObjectW(handle, sizeof(info), &info) == FALSE)
    {
        // Set empty bounds.
        bounds->right = 0;
        bounds->bottom = 0;
    }
    else
    {
        // Set the bounds to the dimensions of the selected image.
        bounds->right = info.bmWidth;
        bounds->bottom = info.bmHeight;
    }

}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
